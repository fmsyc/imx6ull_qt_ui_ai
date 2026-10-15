#pragma once
//
// The shell root window:
//   StatusBar  /  contentStack (desktop pages + embedded apps)  /  DockBar
//
// It wires config/apps.json -> AppPage -> AppTile -> (embedded page | process).
//
#include <QWidget>
#include <QHash>
#include <QPixmap>

#include "core/AppEntry.h"

class AppLauncher;
class IAppPage;
class PagerWidget;

namespace Ui { class DesktopWindow; }

class DesktopWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DesktopWindow(QWidget *parent = nullptr);
    ~DesktopWindow() override;

    // Preview/debug helper: jump directly to a desktop grid page.
    void gotoDesktopPage(int index);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void openApp(const QString &appId);
    void showDesktop();
    void onDockClicked(const QString &dockId);
    void onPageChanged(int index);

private:
    void buildDesktop();
    void loadBackground();
    void rebuildBackgroundCache();
    IAppPage *ensureEmbeddedPage(const AppEntry &entry);

    Ui::DesktopWindow *ui;
    AppLauncher *m_launcher = nullptr;
    QPixmap m_background;          // original, as loaded from disk
    QPixmap m_bgScaled;            // cover-scaled to the current window size
    QPoint  m_bgOffset;
    QHash<QString, IAppPage *> m_embeddedPages;   // appId -> page
};
