#include "shell/DesktopWindow.h"
#include "ui_DesktopWindow.h"

#include "core/AppRegistry.h"
#include "core/AppLauncher.h"
#include "core/ResourceLocator.h"
#include "apps/AppFactory.h"
#include "apps/IAppPage.h"
#include "shell/AppPage.h"
#include "shell/PagerWidget.h"
#include "shell/PageIndicator.h"
#include "shell/StatusBar.h"
#include "shell/DockBar.h"

#include <QPainter>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QLinearGradient>
#include <QDebug>

DesktopWindow::DesktopWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DesktopWindow)
    , m_launcher(new AppLauncher(this))
{
    ui->setupUi(this);
    setObjectName(QStringLiteral("DesktopWindow"));
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    loadBackground();
    buildDesktop();
}

DesktopWindow::~DesktopWindow()
{
    delete ui;
}

void DesktopWindow::gotoDesktopPage(int index)
{
    if (!ui || !ui->pager)
        return;
    if (index < 0 || index >= ui->pager->pageCount())
        return;
    ui->pager->setCurrentIndex(index, /*animate=*/false);
}

void DesktopWindow::loadBackground()
{
    const QString path = ResourceLocator::path(QStringLiteral("resources/background/desktop.png"));
    m_background = path.isEmpty() ? QPixmap() : QPixmap(path);
    m_bgScaled = QPixmap();
    m_bgOffset = QPoint();
    rebuildBackgroundCache();
}

void DesktopWindow::buildDesktop()
{
    AppRegistry &reg = AppRegistry::instance();

    // --- grid pages -------------------------------------------------------
    for (const PageEntry &pageEntry : reg.pages()) {
        auto *page = new AppPage(pageEntry, ui->pager);
        connect(page, &AppPage::appActivated, this, &DesktopWindow::openApp);
        ui->pager->addPage(page);
    }
    ui->pageIndicator->setCount(ui->pager->pageCount());
    connect(ui->pager, &PagerWidget::currentIndexChanged,
            this, &DesktopWindow::onPageChanged);

    // --- status bar -------------------------------------------------------
    ui->statusBar->setUserName(QStringLiteral("ElniFX"));

    // --- dock -------------------------------------------------------------
    ui->dockBar->buildFromConfig(reg.dock());
    connect(ui->dockBar, &DockBar::dockClicked, this, &DesktopWindow::onDockClicked);

    // --- embedded pages are created lazily, on first activation ----------
    ui->contentStack->setCurrentWidget(ui->desktopPage);
}

IAppPage *DesktopWindow::ensureEmbeddedPage(const AppEntry &entry)
{
    const auto it = m_embeddedPages.constFind(entry.id);
    if (it != m_embeddedPages.constEnd())
        return it.value();

    IAppPage *page = AppFactory::instance().create(entry.id, ui->contentStack);
    if (!page)
        return nullptr;

    connect(page, &IAppPage::requestHome, this, &DesktopWindow::showDesktop);
    ui->contentStack->addWidget(page);
    m_embeddedPages.insert(entry.id, page);
    return page;
}

void DesktopWindow::openApp(const QString &appId)
{
    const AppEntry *entry = AppRegistry::instance().findApp(appId);
    if (!entry) {
        qWarning() << "DesktopWindow: unknown app" << appId;
        return;
    }

    // External apps are separate processes.
    if (entry->isExternal()) {
        m_launcher->launchExternal(*entry);
        return;
    }

    // Embedded apps live inside the shell.
    IAppPage *page = ensureEmbeddedPage(*entry);
    if (!page) {
        qWarning() << "DesktopWindow: no embedded page registered for" << appId;
        return;
    }

    if (auto *cur = qobject_cast<IAppPage *>(ui->contentStack->currentWidget()))
        cur->onDeactivated();

    ui->contentStack->setCurrentWidget(page);
    page->onActivated();
}

void DesktopWindow::showDesktop()
{
    if (auto *cur = qobject_cast<IAppPage *>(ui->contentStack->currentWidget()))
        cur->onDeactivated();
    ui->contentStack->setCurrentWidget(ui->desktopPage);
}

void DesktopWindow::onDockClicked(const QString &dockId)
{
    const DockEntry *d = AppRegistry::instance().findDock(dockId);
    if (d) {
        if (!d->app.isEmpty()) {
            openApp(d->app);
            return;
        }
        if (!d->exec.isEmpty()) {
            m_launcher->launchExternal(d->exec, QStringList(), d->id);
            return;
        }
    }
    if (dockId == QLatin1String("home"))
        showDesktop();
}

void DesktopWindow::onPageChanged(int index)
{
    ui->pageIndicator->setCurrent(index);
}

void DesktopWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    rebuildBackgroundCache();
}

void DesktopWindow::rebuildBackgroundCache()
{
    if (m_background.isNull() || size().isEmpty()) {
        m_bgScaled = QPixmap();
        return;
    }
    m_bgScaled = m_background.scaled(size(),
                                     Qt::KeepAspectRatioByExpanding,
                                     Qt::SmoothTransformation);
    m_bgOffset = QPoint((m_bgScaled.width() - width()) / 2,
                        (m_bgScaled.height() - height()) / 2);
}

void DesktopWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if (!m_bgScaled.isNull()) {
        p.drawPixmap(rect(), m_bgScaled, QRect(m_bgOffset, size()));
    } else {
        QLinearGradient g(0, 0, 0, height());
        g.setColorAt(0.0, QColor(0x16, 0x20, 0x30));
        g.setColorAt(1.0, QColor(0x0B, 0x11, 0x1C));
        p.fillRect(rect(), g);
    }
}

void DesktopWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Home) {
        showDesktop();
        event->accept();
        return;
    }
    QWidget::keyPressEvent(event);
}
