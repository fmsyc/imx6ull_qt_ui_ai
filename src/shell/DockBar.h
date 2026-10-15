#pragma once
//
// Bottom dock. Its buttons come entirely from the "dock" array in
// config/apps.json, so adding / reordering a dock button is a config edit.
//
#include <QWidget>

#include "core/AppEntry.h"

namespace Ui { class DockBar; }

class QToolButton;

class DockBar : public QWidget
{
    Q_OBJECT
public:
    explicit DockBar(QWidget *parent = nullptr);
    ~DockBar() override;

    void buildFromConfig(const QList<DockEntry> &entries);

signals:
    // Emitted with DockEntry::id whenever a dock button is clicked.
    void dockClicked(const QString &id);

private:
    Ui::DockBar *ui;
    QList<QToolButton *> m_buttons;
};
