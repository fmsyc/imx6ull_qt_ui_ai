#include "core/ResourceLocator.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QFontDatabase>
#include <QDebug>

QString ResourceLocator::s_root;
QString ResourceLocator::s_sourceRoot;

void ResourceLocator::init(const QString &applicationDirPath)
{
    s_root = applicationDirPath;
}

void ResourceLocator::setSourceRoot(const QString &sourceRoot)
{
    s_sourceRoot = sourceRoot;
}

QString ResourceLocator::root()
{
    return s_root;
}

QString ResourceLocator::path(const QString &relative)
{
    if (relative.isEmpty())
        return QString();

    // Absolute paths pass through unchanged.
    if (relative.startsWith(QLatin1Char('/')) && QFile::exists(relative))
        return relative;

    // 1) runtime file next to the executable
    const QString runtime = s_root + QLatin1Char('/') + relative;
    if (QFile::exists(runtime))
        return runtime;

    // 2) compiled-in fallback
    const QString embedded = QStringLiteral(":/") + relative;
    if (QFile::exists(embedded))
        return embedded;

    // 3) source tree (dev convenience)
    if (!s_sourceRoot.isEmpty()) {
        const QString src = s_sourceRoot + QLatin1Char('/') + relative;
        if (QFile::exists(src))
            return src;
    }

    return QString();
}

bool ResourceLocator::exists(const QString &relative)
{
    return !path(relative).isEmpty();
}

QString ResourceLocator::styleSheet()
{
    const QString p = path(QStringLiteral("resources/ui/style.qss"));
    if (p.isEmpty())
        return QString();

    QFile f(p);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();
    return QString::fromUtf8(f.readAll());
}

void ResourceLocator::loadFonts()
{
    const QString dir = path(QStringLiteral("resources/fonts"));
    if (dir.isEmpty())
        return;

    QDir d(dir);
    const QStringList filters{ QStringLiteral("*.ttf"), QStringLiteral("*.otf") };
    const QFileInfoList entries = d.entryInfoList(filters, QDir::Files);
    for (const QFileInfo &fi : entries) {
        const int id = QFontDatabase::addApplicationFont(fi.absoluteFilePath());
        if (id < 0)
            qWarning() << "ResourceLocator: failed to load font" << fi.absoluteFilePath();
    }
}
