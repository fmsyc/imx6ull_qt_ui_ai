#pragma once
//
// Plain data structures describing the desktop content.
// Everything here is filled from config/apps.json at runtime.
//
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QList>

// One app icon on the desktop.
struct AppEntry
{
    QString id;                                         // unique key, also used by AppFactory
    QString name;                                       // label under the icon
    QString icon;                                       // relative path, e.g. "resources/icons/camera.png"
    QString type = QStringLiteral("embedded");          // "embedded" | "external"
    QString exec;                                       // external only: executable to launch
    QStringList args;                                   // external only: command line arguments
    bool    daemon = false;                              // external only: start once, no window tracking
    QJsonObject raw;                                     // untouched original object

    bool isExternal() const
    {
        return type.compare(QStringLiteral("external"), Qt::CaseInsensitive) == 0;
    }
};

// One swipeable page of the desktop grid.
struct PageEntry
{
    QString         title;
    QList<AppEntry> apps;
};

// One button of the bottom dock.
struct DockEntry
{
    QString id;         // unique key, reported by DockBar::dockClicked
    QString icon;       // relative path
    QString tip;        // tooltip / label
    QString app;        // optional: app id to launch when clicked
    QString exec;       // optional: external executable to launch when clicked
};
