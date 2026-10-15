#pragma once
//
// Resolves runtime resource paths so that images / stylesheets / fonts can be
// replaced on the device WITHOUT recompiling the application.
//
// Lookup order for a relative path like "resources/icons/camera.png":
//   1. <applicationDirPath>/resources/icons/camera.png   (runtime file)
//   2. :/resources/icons/camera.png                      (compiled fallback)
//   3. <sourceRoot>/resources/icons/camera.png           (dev fallback, optional)
//
#include <QString>

class ResourceLocator
{
public:
    // Call once, early in main(), with QCoreApplication::applicationDirPath().
    static void init(const QString &applicationDirPath);

    // Optional extra search root (e.g. the source tree while developing).
    static void setSourceRoot(const QString &sourceRoot);

    // Absolute path to an existing resource, or an empty string if not found.
    static QString path(const QString &relative);

    // Convenience: does the file exist (file system or qrc)?
    static bool exists(const QString &relative);

    // Load the global stylesheet ("resources/ui/style.qss").
    static QString styleSheet();

    // Register every *.ttf / *.otf found in "resources/fonts".
    static void loadFonts();

    static QString root();

private:
    static QString s_root;
    static QString s_sourceRoot;
};
