#include "shell/AppTile.h"
#include "ui_AppTile.h"

#include "core/IconUtil.h"
#include "core/Compat.h"

#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

AppTile::AppTile(const AppEntry &entry, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AppTile)
    , m_entry(entry)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover, true);
    setObjectName(QStringLiteral("AppTile"));

    ui->nameLabel->setText(m_entry.name);
    refreshIcon();
}

AppTile::~AppTile()
{
    delete ui;
}

void AppTile::setIconSize(int logicalPixels)
{
    m_iconSize = logicalPixels;
    ui->iconLabel->setFixedSize(logicalPixels, logicalPixels);
    refreshIcon();
}

void AppTile::refreshIcon()
{
    const int px = qRound(m_iconSize * devicePixelRatioF());
    QPixmap pm = IconUtil::load(m_entry.icon, px, m_entry.name);
    pm.setDevicePixelRatio(devicePixelRatioF());
    ui->iconLabel->setPixmap(pm);
}

void AppTile::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton && rect().contains(compat::mousePos(event)))
        emit activated(m_entry.id);
}
