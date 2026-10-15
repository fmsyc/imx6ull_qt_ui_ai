#pragma once
//
// Spawns "external" apps as child processes and keeps track of them.
// External apps are ordinary executables (the user's existing demos) that the
// desktop simply starts; embedded apps are handled by AppFactory instead.
//
#include <QObject>
#include <QHash>

#include "core/AppEntry.h"

class QProcess;

class AppLauncher : public QObject
{
    Q_OBJECT
public:
    explicit AppLauncher(QObject *parent = nullptr);
    ~AppLauncher() override;

    // Launch an external app (AppEntry::isExternal() == true).
    // If the app is already running and not a daemon, it is brought back by
    // raising the signal below (the concrete implementation decides how).
    bool launchExternal(const AppEntry &entry);

    bool launchExternal(const QString &exec, const QStringList &args, const QString &key = QString());

    bool isRunning(const QString &key) const;

signals:
    void externalStarted(const QString &key);
    void externalFinished(const QString &key, int exitCode);

private slots:
    void onProcessFinished(int exitCode);

private:
    QHash<QString, QProcess *> m_processes;
};
