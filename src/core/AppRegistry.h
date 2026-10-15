#pragma once
//
// Loads config/apps.json into PageEntry / DockEntry lists.
// This is the single place that knows the desktop layout, so adding an app
// never requires touching the C++ sources.
//
#include "core/AppEntry.h"

class AppRegistry
{
public:
    // Load from a relative path resolved by ResourceLocator, e.g. "config/apps.json".
    bool load(const QString &relativeJsonPath);

    const QList<PageEntry> &pages() const { return m_pages; }
    const QList<DockEntry> &dock()  const { return m_dock; }

    // Convenience lookups.
    const AppEntry *findApp(const QString &id) const;
    const DockEntry *findDock(const QString &id) const;

    const QString &errorString() const { return m_error; }

    // Process-wide instance.
    static AppRegistry &instance();

private:
    QList<PageEntry> m_pages;
    QList<DockEntry> m_dock;
    QString          m_error;
};
