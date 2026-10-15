#include "apps/AppFactory.h"
#include "apps/IAppPage.h"

// --- built-in demo apps (replace / extend with your own) ---------------------
#include "apps/camera/CameraPage.h"
#include "apps/placeholder/PlaceholderPage.h"

// The mqtt page needs Qt Mqtt.  CMake defines HAVE_QT_MQTT only when the module
// was found (always true on the board SDK, usually false on a plain Qt6 kit).
// Without it, src/apps/mqtt/MqttUnavailablePage.cpp registers the same app id.
#ifdef HAVE_QT_MQTT
#  include "apps/mqtt/mqtt_client.h"
#endif
// ----------------------------------------------------------------------------

#include <QDebug>

AppFactory &AppFactory::instance()
{
    static AppFactory inst;
    return inst;
}

void AppFactory::reg(const QString &id, Creator creator)
{
    if (id.isEmpty() || !creator) {
        qWarning() << "AppFactory: invalid registration for" << id;
        return;
    }
    m_creators.insert(id, std::move(creator));
}

bool AppFactory::contains(const QString &id) const
{
    return m_creators.contains(id);
}

IAppPage *AppFactory::create(const QString &id, QWidget *parent) const
{
    const auto it = m_creators.constFind(id);
    if (it == m_creators.constEnd())
        return nullptr;
    return (*it)(id, parent);
}

// ---------------------------------------------------------------------------
// Registry table. Keep the ids in sync with config/apps.json.
// ---------------------------------------------------------------------------
// Every id below MUST have a matching entry in config/apps.json; ids that are
// missing here simply fall through to the external-process launcher.
REGISTER_APP("camera",   CameraPage)
REGISTER_APP("media",    PlaceholderPage)
REGISTER_APP("music",    PlaceholderPage)
REGISTER_APP("radio",    PlaceholderPage)
REGISTER_APP("gallery",  PlaceholderPage)
REGISTER_APP("record",   PlaceholderPage)
REGISTER_APP("device",   PlaceholderPage)
REGISTER_APP("serial",   PlaceholderPage)
REGISTER_APP("network",  PlaceholderPage)
REGISTER_APP("settings", PlaceholderPage)

#ifdef HAVE_QT_MQTT
REGISTER_APP("mqtt",    mqtt_client)
#endif
