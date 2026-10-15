#pragma once
//
// A single desktop icon cell (icon + label). Clicking it emits activated(id)
// and the shell decides what to do (embed a page or spawn a process).
//
#include <QFrame>

#include "core/AppEntry.h"

namespace Ui { class AppTile; }

class AppTile : public QFrame
{
    Q_OBJECT
public:
    explicit AppTile(const AppEntry &entry, QWidget *parent = nullptr);
    ~AppTile() override;

    QString appId() const { return m_entry.id; }
    const AppEntry &entry() const { return m_entry; }

    // Redraw the icon at the given logical size (call on DPI / size changes).
    void setIconSize(int logicalPixels);

signals:
    void activated(const QString &appId);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void refreshIcon();

    Ui::AppTile *ui;
    AppEntry m_entry;
    int m_iconSize = 80;
};
