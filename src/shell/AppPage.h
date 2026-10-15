#pragma once
//
// One swipeable page of the desktop. It owns a grid of AppTile widgets that
// are built from a PageEntry (config/apps.json). The number of columns adapts
// to the page width so the same .ui works on other resolutions.
//
#include <QWidget>

#include "core/AppEntry.h"

namespace Ui { class AppPage; }

class AppTile;

class AppPage : public QWidget
{
    Q_OBJECT
public:
    explicit AppPage(const PageEntry &page, QWidget *parent = nullptr);
    ~AppPage() override;

    QString pageTitle() const { return m_page.title; }
    QList<AppTile *> tiles() const { return m_tiles; }

signals:
    void appActivated(const QString &appId);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void relayoutGrid();

    Ui::AppPage *ui;
    PageEntry     m_page;
    QList<AppTile *> m_tiles;
    int m_columns = 0;
};
