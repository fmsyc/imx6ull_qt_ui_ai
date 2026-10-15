#include "shell/StatusBar.h"
#include "ui_StatusBar.h"

#include "core/IconUtil.h"

#include <QTimer>
#include <QTime>
#include <QLabel>

StatusBar::StatusBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatusBar)
    , m_clockTimer(new QTimer(this))
{
    ui->setupUi(this);
    setObjectName(QStringLiteral("StatusBar"));

    ui->micIcon->setPixmap(IconUtil::load(QStringLiteral("resources/icons/status_mic.png"), 18, QStringLiteral("M")));
    ui->avatarLabel->setPixmap(IconUtil::load(QStringLiteral("resources/icons/status_avatar.png"), 28, QStringLiteral("E")));
    ui->wifiLabel->setPixmap(IconUtil::load(QStringLiteral("resources/icons/status_wifi.png"), 20, QStringLiteral("W")));
    ui->signalLabel->setPixmap(IconUtil::load(QStringLiteral("resources/icons/status_signal.png"), 20, QStringLiteral("S")));

    connect(m_clockTimer, &QTimer::timeout, this, &StatusBar::updateClock);
    m_clockTimer->start(10 * 1000);
    updateClock();
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::setHintText(const QString &text)
{
    ui->hintLabel->setText(text);
}

void StatusBar::setUserName(const QString &name)
{
    ui->userLabel->setText(name);
}

void StatusBar::updateClock()
{
    ui->clockLabel->setText(QTime::currentTime().toString(QStringLiteral("H:mm")));
}
