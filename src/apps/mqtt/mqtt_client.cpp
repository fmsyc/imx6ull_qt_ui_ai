#include "mqtt_client.h"
#include "ui_mqtt_client.h"

#include <QDateTime>
#include <QListWidgetItem>
#include <QPushButton>

mqtt_client::mqtt_client(const QString &appId, QWidget *parent)
    : IAppPage(appId, parent)
    , ui(new Ui::mqtt_client)
{
    ui->setupUi(this);

    // --- client ----------------------------------------------------------
    m_mqttClient = new QMqttClient(this);

    // --- Tab 1: connection ------------------------------------------------
    connect(ui->btn_apply, &QPushButton::clicked, this, &mqtt_client::applyConnectSlot);
    connect(m_mqttClient, &QMqttClient::connected, this, &mqtt_client::onConnectedSlot);
    connect(m_mqttClient, &QMqttClient::disconnected, this, &mqtt_client::onDisconnectedSlot);
    connect(m_mqttClient, &QMqttClient::errorChanged, this, &mqtt_client::onErrorChangedSlot);

    // --- Tab 2: publish ---------------------------------------------------
    connect(ui->btn_add, &QPushButton::clicked, this, &mqtt_client::addTopicSlot);
    connect(ui->btn_public, &QPushButton::clicked, this, &mqtt_client::publishMsgSlot);

    // --- Tab 3: subscribe / receive ---------------------------------------
    // comboBox_2 doubles as "type a new topic" and "pick a subscribed topic".
    ui->comboBox_2->setEditable(true);
    connect(ui->btn_subscribe, &QPushButton::clicked, this, &mqtt_client::subscribeTopicSlot);
    connect(m_mqttClient, &QMqttClient::messageReceived,
            this, &mqtt_client::onMessageReceivedSlot);
    connect(ui->comboBox_2, &QComboBox::currentTextChanged,
            this, &mqtt_client::onFilterTopicChangedSlot);

    ui->btn_apply->setText(QStringLiteral("连接"));
}

mqtt_client::~mqtt_client()
{
    delete ui;
}

void mqtt_client::onActivated()
{
    qInfo() << "mqtt_client: activated" << appId();
}

void mqtt_client::onDeactivated()
{
    qInfo() << "mqtt_client: deactivated" << appId();
}

void mqtt_client::setStatus(const QString &text)
{
    ui->btn_apply->setText(text);
}

// ---------------------------------------------------------------------------
// Tab 1: connect
// ---------------------------------------------------------------------------
void mqtt_client::applyConnectSlot()
{
    // Toggle: a second press while connected disconnects.
    if (m_mqttClient->state() != QMqttClient::Disconnected) {
        m_mqttClient->disconnectFromHost();
        return;
    }

    const QString ip = ui->lineEdit_ip->text().trimmed();
    const QString clientId = ui->lineEdit_id->text().trimmed();
    const QString portText = ui->lineEdit_port->text().trimmed();

    if (ip.isEmpty() || clientId.isEmpty()) {
        setStatus(QStringLiteral("请填写地址和 ID"));
        return;
    }

    bool ok = false;
    const uint port = portText.toUInt(&ok);
    if (!ok || port == 0 || port > 65535) {
        setStatus(QStringLiteral("端口无效"));
        return;
    }

    m_mqttClient->setHostname(ip);
    m_mqttClient->setPort(static_cast<quint16>(port));
    m_mqttClient->setClientId(clientId);

    setStatus(QStringLiteral("连接中…"));
    m_mqttClient->connectToHost();
}

void mqtt_client::onConnectedSlot()
{
    setStatus(QStringLiteral("已连接"));
    ui->btn_apply->setEnabled(true);

    // Re-establish the subscriptions shown in the list (e.g. after a reconnect).
    for (int i = 0; i < ui->textEdit_subscribe_name->count(); ++i) {
        const QString topic = ui->textEdit_subscribe_name->item(i)->text();
        if (!topic.isEmpty())
            m_mqttClient->subscribe(QMqttTopicFilter(topic), 0);
    }
}

void mqtt_client::onDisconnectedSlot()
{
    setStatus(QStringLiteral("连接"));
    ui->btn_apply->setEnabled(true);
}

void mqtt_client::onErrorChangedSlot(QMqttClient::ClientError error)
{
    if (error == QMqttClient::NoError)
        return;

    // Keep it simple on an embedded target: report through the button label.
    setStatus(QStringLiteral("失败: %1").arg(static_cast<int>(error)));
    ui->btn_apply->setEnabled(true);
    qWarning() << "mqtt_client: error" << error;
}

// ---------------------------------------------------------------------------
// Tab 2: publish
// ---------------------------------------------------------------------------
void mqtt_client::addTopicSlot()
{
    const QString newTopic = ui->textEdit_input_title->toPlainText().trimmed();
    if (newTopic.isEmpty())
        return;

    if (ui->comboBox->findText(newTopic) == -1) {
        ui->comboBox->addItem(newTopic);
        ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
    }
    ui->textEdit_input_title->clear();
}

void mqtt_client::publishMsgSlot()
{
    if (m_mqttClient->state() != QMqttClient::Connected) {
        ui->textBrowser_publish_info->append(QStringLiteral("未连接，无法发布。"));
        return;
    }

    const QString topic = ui->comboBox->currentText().trimmed();
    const QString payload = ui->textEdit_output_context->toPlainText();

    if (topic.isEmpty() || payload.isEmpty())
        return;

    m_mqttClient->publish(QMqttTopicName(topic), payload.toUtf8(), 0);
    ui->textBrowser_publish_info->append(
        QStringLiteral("[%1] %2: %3")
            .arg(QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss")),
                 topic, payload));

    ui->textEdit_output_context->clear();
}

// ---------------------------------------------------------------------------
// Tab 3: subscribe / receive
// ---------------------------------------------------------------------------
void mqtt_client::subscribeTopicSlot()
{
    const QString subTopic = ui->comboBox_2->currentText().trimmed();
    if (subTopic.isEmpty())
        return;

    if (m_mqttClient->state() != QMqttClient::Connected) {
        ui->listWidget->addItem(QStringLiteral("未连接，无法订阅 %1").arg(subTopic));
        return;
    }

    // Subscribe again on purpose: re-subscribing an existing filter is a no-op
    // on the broker side and lets the user retry after a failed attempt.
    auto subscription = m_mqttClient->subscribe(QMqttTopicFilter(subTopic), 0);
    qInfo() << "mqtt_client: subscribe" << subTopic << "->" << bool(subscription);
}

void mqtt_client::onMessageReceivedSlot(const QByteArray &message, const QMqttTopicName &topic)
{
    const QString topicName = topic.name();
    const QString timeStr =
        QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"));
    const QString text = QString::fromUtf8(message);

    const QString formattedMsg =
        QStringLiteral("[%1] %2:\n%3\n").arg(timeStr, topicName, text);

    // 1. Keep this topic's history.
    m_topicMessages[topicName].append(formattedMsg);

    // 2. Register the topic the first time a message arrives on it, so the user
    //    can pick it in comboBox_2 without typing it again.
    if (ui->comboBox_2->findText(topicName) == -1)
        ui->comboBox_2->addItem(topicName);

    if (ui->textEdit_subscribe_name->findItems(topicName, Qt::MatchExactly).isEmpty())
        ui->textEdit_subscribe_name->addItem(topicName);

    // 3. Live-refresh the right-hand pane when this topic is the selected one.
    if (ui->comboBox_2->currentText() == topicName)
        ui->textEdit_recContext->append(formattedMsg);
}

void mqtt_client::onFilterTopicChangedSlot(const QString &topicName)
{
    ui->textEdit_recContext->clear();
    if (m_topicMessages.contains(topicName))
        ui->textEdit_recContext->setPlainText(m_topicMessages.value(topicName));
}

// ---------------------------------------------------------------------------
// Back to the desktop.  The shell owns and caches this page, so only ask it to
// switch back -- never deleteLater() ourselves.
// ---------------------------------------------------------------------------
void mqtt_client::on_btn_cancel_clicked()
{
    ui->btn_cancel->hide();
    emit requestHome();
}
