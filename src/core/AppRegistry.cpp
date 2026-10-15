#include "core/AppRegistry.h"
#include "core/ResourceLocator.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

namespace {

AppEntry parseApp(const QJsonObject &o)
{
    AppEntry e;
    e.id     = o.value(QStringLiteral("id")).toString();
    e.name   = o.value(QStringLiteral("name")).toString(e.id);
    e.icon   = o.value(QStringLiteral("icon")).toString();
    e.type   = o.value(QStringLiteral("type")).toString(QStringLiteral("embedded"));
    e.exec   = o.value(QStringLiteral("exec")).toString();
    e.daemon = o.value(QStringLiteral("daemon")).toBool(false);
    const QJsonArray args = o.value(QStringLiteral("args")).toArray();
    for (const QJsonValue &v : args)
        e.args << v.toString();
    e.raw = o;
    return e;
}

DockEntry parseDock(const QJsonObject &o)
{
    DockEntry d;
    d.id   = o.value(QStringLiteral("id")).toString();
    d.icon = o.value(QStringLiteral("icon")).toString();
    d.tip  = o.value(QStringLiteral("tip")).toString(d.id);
    d.app  = o.value(QStringLiteral("app")).toString();
    d.exec = o.value(QStringLiteral("exec")).toString();
    return d;
}

} // namespace

AppRegistry &AppRegistry::instance()
{
    static AppRegistry inst;
    return inst;
}

bool AppRegistry::load(const QString &relativeJsonPath)
{
    m_pages.clear();
    m_dock.clear();
    m_error.clear();

    const QString file = ResourceLocator::path(relativeJsonPath);
    if (file.isEmpty()) {
        m_error = QStringLiteral("apps.json not found: ") + relativeJsonPath;
        qWarning() << "AppRegistry:" << m_error;
        return false;
    }

    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_error = QStringLiteral("cannot open ") + file;
        qWarning() << "AppRegistry:" << m_error;
        return false;
    }

    QJsonParseError err{};
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        m_error = QStringLiteral("invalid JSON in ") + file + QStringLiteral(": ") + err.errorString();
        qWarning() << "AppRegistry:" << m_error;
        return false;
    }

    const QJsonObject root = doc.object();

    const QJsonArray pages = root.value(QStringLiteral("pages")).toArray();
    for (const QJsonValue &pv : pages) {
        const QJsonObject po = pv.toObject();
        PageEntry page;
        page.title = po.value(QStringLiteral("title")).toString();
        const QJsonArray apps = po.value(QStringLiteral("apps")).toArray();
        for (const QJsonValue &av : apps)
            page.apps << parseApp(av.toObject());
        if (!page.apps.isEmpty())
            m_pages << page;
    }

    const QJsonArray dock = root.value(QStringLiteral("dock")).toArray();
    for (const QJsonValue &dv : dock)
        m_dock << parseDock(dv.toObject());

    qInfo() << "AppRegistry: loaded" << m_pages.size() << "page(s),"
            << m_dock.size() << "dock item(s) from" << file;
    return true;
}

const AppEntry *AppRegistry::findApp(const QString &id) const
{
    for (const PageEntry &p : m_pages) {
        for (const AppEntry &a : p.apps) {
            if (a.id == id)
                return &a;
        }
    }
    return nullptr;
}

const DockEntry *AppRegistry::findDock(const QString &id) const
{
    for (const DockEntry &d : m_dock) {
        if (d.id == id)
            return &d;
    }
    return nullptr;
}
