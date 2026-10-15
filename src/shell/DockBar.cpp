#include "shell/DockBar.h"
#include "ui_DockBar.h"

#include "core/IconUtil.h"

#include <QToolButton>
#include <QHBoxLayout>
#include <QLayoutItem>

DockBar::DockBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DockBar)
{
    ui->setupUi(this);
    setObjectName(QStringLiteral("DockBar"));
}

DockBar::~DockBar()
{
    delete ui;
}

void DockBar::buildFromConfig(const QList<DockEntry> &entries)
{
    // Wipe the previous content (buttons + spacer items).
    while (QLayoutItem *item = ui->dockLayout->takeAt(0)) {
        if (QWidget *w = item->widget()) {
            w->hide();
            w->deleteLater();
        }
        delete item;
    }
    m_buttons.clear();

    for (const DockEntry &e : entries) {
        ui->dockLayout->addStretch(1);

        auto *btn = new QToolButton(ui->dockPanel);
        btn->setObjectName(QStringLiteral("DockButton"));
        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn->setAutoRaise(true);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setIconSize(QSize(40, 40));
        btn->setFixedSize(64, 56);
        btn->setToolTip(e.tip);
        btn->setIcon(QIcon(IconUtil::load(e.icon, 40, e.tip)));

        const QString id = e.id;
        connect(btn, &QToolButton::clicked, this, [this, id]() { emit dockClicked(id); });

        ui->dockLayout->addWidget(btn);
        m_buttons.append(btn);
    }
    ui->dockLayout->addStretch(1);
}
