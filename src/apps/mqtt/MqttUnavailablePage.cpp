//
// Fallback page compiled ONLY when Qt Mqtt is not available (typical for a
// plain Qt6 desktop kit).  It keeps the app id "mqtt" registered so the shell
// never falls through to the external-process launcher, and it tells the user
// what to install instead of showing a blank/broken page.
//
// On the board the real page (mqtt_client) is used, because the FSL/Yocto SDK
// ships Qt5Mqtt.
//
#include "apps/IAppPage.h"

#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>

namespace {

class MqttUnavailablePage : public IAppPage
{
public:
    explicit MqttUnavailablePage(const QString &appId, QWidget *parent = nullptr)
        : IAppPage(appId, parent)
    {
        auto *layout = new QVBoxLayout(this);

        auto *back = new QToolButton(this);
        back->setText(QStringLiteral("←"));
        back->setAutoRaise(true);
        connect(back, &QToolButton::clicked, this, &IAppPage::requestHome);
        layout->addWidget(back, 0, Qt::AlignLeft);

        auto *label = new QLabel(this);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        label->setText(QStringLiteral(
            "当前 Qt 未包含 Mqtt 模块，MQTT 页面未编译。\n\n"
            "桌面端：用 Qt Maintenance Tool 安装 “Qt Mqtt” 附加模块后重新 make。\n"
            "板端：FSL/Yocto SDK 自带 Qt5Mqtt，`make board` 会正常编入该页面。"));
        layout->addWidget(label, 1);
    }
};

} // namespace

#include "apps/AppFactory.h"
REGISTER_APP("mqtt", MqttUnavailablePage)
