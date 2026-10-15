#pragma once
//
// Every EMBEDDED app page implements this interface.
//
// To add a new embedded app:
//   1. create  src/apps/<name>/<Name>Page.{h,cpp,ui}
//   2. inherit IAppPage, implement onActivated()/onDeactivated() as needed
//   3. register it once in src/apps/AppFactory.cpp with REGISTER_APP("id", Class)
//   4. add an entry to config/apps.json with the same "id"
//
#include <QWidget>
#include <QString>

class IAppPage : public QWidget
{
    Q_OBJECT
public:
    // "appId" must match the "id" field in config/apps.json.
    explicit IAppPage(const QString &appId, QWidget *parent = nullptr)
        : QWidget(parent)
        , m_appId(appId)
    {
    }
    ~IAppPage() override = default;

    QString appId() const { return m_appId; }

    // Called when the page becomes visible / hidden inside the shell.
    // Use these to start / stop camera previews, timers, polling, etc.
    virtual void onActivated() {}
    virtual void onDeactivated() {}

signals:
    // Ask the shell to return to the desktop (e.g. the "back" button).
    void requestHome();

private:
    QString m_appId;
};
