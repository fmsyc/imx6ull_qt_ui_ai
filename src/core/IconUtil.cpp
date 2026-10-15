#include "core/IconUtil.h"
#include "core/ResourceLocator.h"

#include <QPainter>
#include <QLinearGradient>
#include <QFont>

namespace IconUtil {

QPixmap placeholder(const QString &text, int px)
{
    QPixmap pm(px, px);
    pm.fill(Qt::transparent);

    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient g(0, 0, px, px);
    g.setColorAt(0.0, QColor(0x5A, 0x7C, 0xFF));
    g.setColorAt(1.0, QColor(0x35, 0xC8, 0xD8));
    p.setPen(Qt::NoPen);
    p.setBrush(g);
    p.drawRoundedRect(QRectF(0, 0, px, px), px * 0.24, px * 0.24);

    if (!text.isEmpty()) {
        QFont f = p.font();
        f.setPixelSize(static_cast<int>(px * 0.42));
        f.setBold(true);
        p.setFont(f);
        p.setPen(QColor(255, 255, 255, 230));
        p.drawText(QRectF(0, 0, px, px), Qt::AlignCenter, text.left(1));
    }
    return pm;
}

QPixmap load(const QString &relative, int logicalPx, const QString &fallbackText)
{
    const qreal dpr = 1.0; // logicalPx already represents device pixels here
    const int px = qMax(1, qRound(logicalPx * dpr));

    QPixmap result;
    const QString path = ResourceLocator::path(relative);
    if (!path.isEmpty()) {
        const QPixmap source(path);
        if (!source.isNull())
            result = source.scaled(px, px, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    if (result.isNull())
        result = placeholder(fallbackText, px);

    result.setDevicePixelRatio(dpr);
    return result;
}

} // namespace IconUtil
