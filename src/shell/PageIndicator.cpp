#include "shell/PageIndicator.h"

#include <QPainter>

PageIndicator::PageIndicator(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    // Fixed strip at the bottom: it must never compete with the pager for
    // vertical space (otherwise the two widgets split the page in half).
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setFixedHeight(24);
}

void PageIndicator::setCount(int count)
{
    if (count == m_count)
        return;
    m_count = count;
    m_current = qBound(0, m_current, qMax(0, m_count - 1));
    updateGeometry();
    update();
}

void PageIndicator::setCurrent(int index)
{
    if (index == m_current)
        return;
    m_current = index;
    update();
}

QSize PageIndicator::sizeHint() const
{
    if (m_count <= 0)
        return QSize(0, 24);
    const int w = m_count * m_dotSize + (m_count - 1) * m_spacing;
    return QSize(w, 24);
}

void PageIndicator::paintEvent(QPaintEvent *)
{
    if (m_count <= 0)
        return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    const int total = m_count * m_dotSize + (m_count - 1) * m_spacing;
    int x = (width() - total) / 2;
    const int y = (height() - m_dotSize) / 2;

    for (int i = 0; i < m_count; ++i) {
        const bool active = (i == m_current);
        p.setBrush(active ? QColor(255, 255, 255, 235) : QColor(255, 255, 255, 80));
        const int d = active ? m_dotSize : m_dotSize - 2;
        p.drawEllipse(QRectF(x + (m_dotSize - d) / 2.0,
                             y + (m_dotSize - d) / 2.0,
                             d, d));
        x += m_dotSize + m_spacing;
    }
}
