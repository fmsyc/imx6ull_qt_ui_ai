#pragma once
//
// Small helpers that hide Qt5 / Qt6 API differences.
// The board runs Qt 5.12.9, the desktop dev machine runs Qt 6.x, so the code
// base has to compile cleanly against both.
//
#include <QtGlobal>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QPixmap>
#include <QScreen>

namespace compat {

// QMouseEvent::pos() is deprecated/removed in some Qt6 builds.
inline QPoint mousePos(const QMouseEvent *e)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return e->position().toPoint();
#else
    return e->pos();
#endif
}

// QFontMetrics::width() -> horizontalAdvance() since Qt 5.11.
inline int textWidth(const QFontMetrics &fm, const QString &text)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    return fm.horizontalAdvance(text);
#else
    return fm.width(text);
#endif
}

// Device pixel ratio safe scaling for a target logical size.
inline QPixmap scaledPixmap(const QPixmap &src, const QSize &logical, qreal dpr)
{
    QPixmap out = src.scaled(logical * dpr,
                             Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    out.setDevicePixelRatio(dpr);
    return out;
}

} // namespace compat
