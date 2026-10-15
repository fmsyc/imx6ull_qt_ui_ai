#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "apps/IAppPage.h"

#include <QMap>
#include <QWidget>

#include <QMqttClient>

namespace Ui {
class mqtt_client;
}

// Embedded MQTT page (app id "mqtt" in config/apps.json).
//
// Only compiled when Qt Mqtt is available (see CMakeLists.txt / HAVE_QT_MQTT).
class mqtt_client : public IAppPage
{
    Q_OBJECT

public:
    explicit mqtt_client(const QString &appId, QWidget *parent = nullptr);
    ~mqtt_client() override;

    void onActivated() override;
    void onDeactivated() override;

private slots:
    // Tab 1: connection
    void applyConnectSlot();
    void onConnectedSlot();
    void onDisconnectedSlot();
    void onErrorChangedSlot(QMqttClient::ClientError error);

    // Tab 2: publish
    void addTopicSlot();
    void publishMsgSlot();

    // Tab 3: subscribe + receive
    void subscribeTopicSlot();
    void onMessageReceivedSlot(const QByteArray &message, const QMqttTopicName &topic);
    void onFilterTopicChangedSlot(const QString &topicName);

    void on_btn_cancel_clicked();

private:
    void setStatus(const QString &text);

    Ui::mqtt_client *ui = nullptr;
    QMqttClient *m_mqttClient = nullptr;

    // topic -> all formatted messages received on it
    QMap<QString, QString> m_topicMessages;
};

#endif // MQTT_CLIENT_H
