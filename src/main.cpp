//
// TerminalApp - Qt Widgets desktop shell for embedded Linux (i.MX6ULL).
//
// Startup sequence:
//   1. create the application (with high-DPI handling that works on both Qt5/6)
//   2. point ResourceLocator at the executable directory (+ source tree in dev)
//   3. load the runtime stylesheet and any bundled fonts
//   4. parse config/apps.json
//   5. show the shell window
//
// Nothing below is board specific; the only thing that changes between the
// desktop dev machine and the board is the CMake toolchain.
//
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QFont>
#include <QIcon>
#include <QTimer>
#include <QMetaObject>

#include "core/ResourceLocator.h"
#include "core/AppRegistry.h"
#include "shell/DesktopWindow.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // Qt6 enables this by default; Qt5 needs it explicitly.
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("TerminalApp"));
    app.setApplicationDisplayName(QStringLiteral("TerminalApp"));
    app.setOrganizationName(QStringLiteral("ElniFX"));
    app.setApplicationVersion(QStringLiteral("1.0.0"));

    // --- runtime paths ----------------------------------------------------
    ResourceLocator::init(QCoreApplication::applicationDirPath());
#ifdef TERMINALAPP_SOURCE_DIR
    // Dev convenience: if config/resources are not next to the binary yet,
    // fall back to the source tree. Harmless on the board.
    ResourceLocator::setSourceRoot(QStringLiteral(TERMINALAPP_SOURCE_DIR));
#endif

    ResourceLocator::loadFonts();

    // --- global stylesheet ------------------------------------------------
    const QString qss = ResourceLocator::styleSheet();
    if (!qss.isEmpty())
        app.setStyleSheet(qss);
    else
        qWarning() << "TerminalApp: style.qss not found, using default look";

    // --- desktop layout ---------------------------------------------------
    if (!AppRegistry::instance().load(QStringLiteral("config/apps.json"))) {
        qWarning() << "TerminalApp: falling back to an empty desktop:"
                   << AppRegistry::instance().errorString();
    }

    // --- window -----------------------------------------------------------
    DesktopWindow window;
    window.setWindowTitle(QStringLiteral("TerminalApp"));
    window.resize(1024, 576);

    const QStringList args = app.arguments();

    // dev / preview helpers ------------------------------------------------
    //   --fullscreen        show fullscreen (board + demos)
    //   --page N            jump straight to desktop page N (0 based)
    //   --open APPID        open an app immediately (embedded or external)
    //   --screenshot FILE   render the window to FILE and exit; pair it with
    //                       QT_QPA_PLATFORM=offscreen for a headless preview
    const int pageArg = args.indexOf(QStringLiteral("--page"));
    if (pageArg > 0 && pageArg + 1 < args.size())
        window.gotoDesktopPage(args.at(pageArg + 1).toInt());

    if (args.contains(QStringLiteral("--fullscreen")))
        window.showFullScreen();
    else
        window.show();

    const int openArg = args.indexOf(QStringLiteral("--open"));
    if (openArg > 0 && openArg + 1 < args.size())
        QMetaObject::invokeMethod(&window, "openApp", Qt::DirectConnection,
                                  Q_ARG(QString, args.at(openArg + 1)));

    const int shotArg = args.indexOf(QStringLiteral("--screenshot"));
    if (shotArg > 0 && shotArg + 1 < args.size()) {
        const QString path = args.at(shotArg + 1);
        QTimer::singleShot(500, &app, [&window, &app, path]() {
            if (window.grab().save(path))
                qInfo() << "TerminalApp: screenshot written to" << path;
            else
                qWarning() << "TerminalApp: could not write screenshot" << path;
            app.quit();
        });
    }

    return app.exec();
}
