#pragma once
//
// Maps an app id (from config/apps.json) to a concrete IAppPage subclass.
// Registration is done once, in AppFactory.cpp, with the REGISTER_APP macro.
//
#include <QHash>
#include <QString>
#include <functional>

class IAppPage;
class QWidget;

class AppFactory
{
public:
    // (id, parent) -> page
    using Creator = std::function<IAppPage *(const QString &, QWidget *)>;

    static AppFactory &instance();

    void reg(const QString &id, Creator creator);
    bool contains(const QString &id) const;

    // Returns a freshly created page, or nullptr when the id is unknown
    // (the shell then falls back to the external-process launcher).
    IAppPage *create(const QString &id, QWidget *parent) const;

private:
    QHash<QString, Creator> m_creators;
};

// --- registration helpers ---------------------------------------------------
#define APP_REG_CAT2(a, b) a##b
#define APP_REG_CAT(a, b) APP_REG_CAT2(a, b)

// Register an embedded app page:  REGISTER_APP("camera", CameraPage)
// The same class may be registered under several ids (see PlaceholderPage).
#define REGISTER_APP(ID, CLASS)                                                          \
    namespace {                                                                          \
    const bool APP_REG_CAT(qtAppReg_, __COUNTER__) =                                     \
        (AppFactory::instance().reg(QStringLiteral(ID),                                  \
                                    [](const QString &id, QWidget *parent) -> IAppPage * { \
                                        return new CLASS(id, parent);                    \
                                    }),                                                  \
         true);                                                                          \
    }
