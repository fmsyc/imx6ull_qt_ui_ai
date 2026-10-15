#include "shell/AppPage.h"
#include "ui_AppPage.h"
#include "shell/AppTile.h"

#include <QGridLayout>
#include <QResizeEvent>
#include <QLabel>

namespace {
// Preferred tile footprint; used to decide how many columns fit.
constexpr int kTileWidth = 150;
constexpr int kTileHeight = 128;   // must match AppTile's fixed size in AppTile.ui
constexpr int kMinColumns = 3;
} // namespace

AppPage::AppPage(const PageEntry &page, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppPage)
    , m_page(page)
{
    ui->setupUi(this);
    setObjectName(QStringLiteral("AppPage"));

    if (!m_page.title.isEmpty()) {
        ui->titleLabel->setText(m_page.title);
        ui->titleLabel->setVisible(true);
    }

    for (const AppEntry &entry : m_page.apps) {
        auto *tile = new AppTile(entry, this);
        connect(tile, &AppTile::activated, this, &AppPage::appActivated);
        m_tiles.append(tile);
    }
}

AppPage::~AppPage()
{
    delete ui;
}

void AppPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    relayoutGrid();
}

void AppPage::relayoutGrid()
{
    const int spacing = ui->gridLayout->horizontalSpacing();
    const int usable = width() - ui->pageLayout->contentsMargins().left()
                              - ui->pageLayout->contentsMargins().right();
    int columns = (usable + spacing) / (kTileWidth + spacing);
    columns = qMax(kMinColumns, columns);
    if (columns == m_columns)
        return;
    m_columns = columns;

    // Drop the layout items but keep the tile widgets alive.
    while (QLayoutItem *item = ui->gridLayout->takeAt(0))
        delete item;

    int row = 0, col = 0;
    for (AppTile *tile : m_tiles) {
        ui->gridLayout->addWidget(tile, row, col, Qt::AlignCenter);
        if (++col >= columns) {
            col = 0;
            ++row;
        }
    }
}
