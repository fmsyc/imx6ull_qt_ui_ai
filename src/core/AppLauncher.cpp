#include "core/AppLauncher.h"
#include "core/ResourceLocator.h"

#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

AppLauncher::AppLauncher(QObject *parent)
    : QObject(parent)
{
}

AppLauncher::~AppLauncher()
{
    for (QProcess *p : m_processes) {
        if (p->state() != QProcess::NotRunning) {
            p->terminate();
            if (!p->waitForFinished(1500))
                p->kill();
        }
    }
}

bool AppLauncher::launchExternal(const AppEntry &entry)
{
    if (!entry.isExternal()) {
        qWarning() << "AppLauncher: app is not external:" << entry.id;
        return false;
    }
    return launchExternal(entry.exec, entry.args, entry.id);
}

bool AppLauncher::launchExternal(const QString &exec, const QStringList &args, const QString &key)
{
    if (exec.isEmpty()) {
        qWarning() << "AppLauncher: empty exec";
        return false;
    }

    const QString k = key.isEmpty() ? exec : key;
    if (isRunning(k))
        return true; // already up

    // Resolve the program: an absolute path goes straight through, a relative
    // path (e.g. "resources/tools/x.sh") is looked up next to the executable so
    // the config stays portable, and a bare command name goes to PATH.
    QString program = exec;
    if (!QFileInfo(exec).isAbsolute() && exec.contains(QLatin1Char('/'))) {
        const QString resolved = ResourceLocator::path(exec);
        if (!resolved.isEmpty())
            program = resolved;
    }

    auto *proc = new QProcess(this);
    proc->setProgram(program);
    proc->setArguments(args);
    proc->setWorkingDirectory(QFileInfo(program).absolutePath());

    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, k](int code, QProcess::ExitStatus) {
                onProcessFinished(code);
                emit externalFinished(k, code);
            });
    connect(proc, &QProcess::errorOccurred, this, [k](QProcess::ProcessError e) {
        qWarning() << "AppLauncher: process error" << k << e;
    });

    m_processes.insert(k, proc);
    proc->start();

    if (!proc->waitForStarted(3000)) {
        qWarning() << "AppLauncher: failed to start" << exec;
        m_processes.remove(k);
        proc->deleteLater();
        return false;
    }

    emit externalStarted(k);
    return true;
}

bool AppLauncher::isRunning(const QString &key) const
{
    const auto it = m_processes.constFind(key);
    return it != m_processes.constEnd() && (*it)->state() != QProcess::NotRunning;
}

void AppLauncher::onProcessFinished(int exitCode)
{
    auto *proc = qobject_cast<QProcess *>(sender());
    if (!proc)
        return;
    for (auto it = m_processes.begin(); it != m_processes.end(); ++it) {
        if (it.value() == proc) {
            m_processes.erase(it);
            break;
        }
    }
    proc->deleteLater();
    Q_UNUSED(exitCode);
}
