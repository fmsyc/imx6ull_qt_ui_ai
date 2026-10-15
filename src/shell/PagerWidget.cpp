#include "shell/PagerWidget.h"
#include "core/Compat.h"

#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QDateTime>
#include <QtMath>

PagerWidget::PagerWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    // The pager is the only stretchable child of the desktop page. Without an
    // explicit Expanding policy it would split the leftover height with the
    // page indicator (QBoxLayout divides spare space equally between
    // non-stretching items), which squashed the app grid onto two overlapping
    // rows. The indicator is Fixed, so everything left over lands here.
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Touch is translated to mouse events by Qt, so no touch handling is needed.
    m_anim = new QPropertyAnimation(this, "offset", this);
    m_anim->setEasingCurve(QEasingCurve::OutCubic);
}

void PagerWidget::addPage(QWidget *page)
{
    if (!page)
        return;
    page->setParent(this);
    m_pages.append(page);
    relayoutPages();
}

qreal PagerWidget::maxOffset() const
{
    const int n = m_pages.size();
    if (n <= 1)
        return 0.0;
    return static_cast<qreal>(n - 1) * width();
}

void PagerWidget::setOffset(qreal value)
{
    const qreal maxO = maxOffset();
    if (m_dragging) {
        // Rubber band: a soft overshoot is allowed at both ends while dragging.
        if (value < 0.0)
            value *= 0.35;
        else if (value > maxO)
            value = maxO + (value - maxO) * 0.35;
    } else {
        value = qBound(0.0, value, maxO);
    }

    if (qFuzzyCompare(value, m_offset))
        return;
    m_offset = value;
    relayoutPages();
}

void PagerWidget::relayoutPages()
{
    const int w = width();
    const int h = height();
    for (int i = 0; i < m_pages.size(); ++i) {
        const int x = qRound(static_cast<qreal>(i) * w - m_offset);
        m_pages[i]->setGeometry(x, 0, w, h);
    }
}

void PagerWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_offset = static_cast<qreal>(m_index) * width();
    relayoutPages();
}

void PagerWidget::setCurrentIndex(int index, bool animate)
{
    if (m_pages.isEmpty())
        return;
    index = qBound(0, index, m_pages.size() - 1);

    const bool changed = (index != m_index);
    m_index = index;
    if (changed)
        emit currentIndexChanged(m_index);

    if (animate)
        animateToIndex(index);
    else
        setOffset(static_cast<qreal>(index) * width());
}

void PagerWidget::nextPage() { setCurrentIndex(m_index + 1, true); }
void PagerWidget::prevPage() { setCurrentIndex(m_index - 1, true); }

void PagerWidget::animateToIndex(int index)
{
    m_anim->stop();
    m_anim->setDuration(m_duration);
    m_anim->setStartValue(m_offset);
    m_anim->setEndValue(static_cast<qreal>(index) * width());
    m_anim->start();
}

void PagerWidget::mousePressEvent(QMouseEvent *event)
{
    m_anim->stop();
    m_dragging = true;
    m_moved = false;
    m_pressX = m_prevX = compat::mousePos(event).x();
    m_pressOffset = m_offset;
    m_velocity = 0.0;
    m_lastTime = QDateTime::currentMSecsSinceEpoch();
    event->accept();
}

void PagerWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_dragging) {
        event->ignore();
        return;
    }

    const int x = compat::mousePos(event).x();
    const int dx = x - m_pressX;
    if (qAbs(dx) > m_dragThreshold)
        m_moved = true;

    // Velocity of the *content* (px/ms); positive == moving towards next page.
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    const qint64 dt = now - m_lastTime;
    if (dt > 0) {
        const qreal dOffset = -static_cast<qreal>(x - m_prevX);
        m_velocity = dOffset / static_cast<qreal>(dt);
        m_lastTime = now;
    }
    m_prevX = x;

    setOffset(m_pressOffset - dx);
    event->accept();
}

void PagerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_dragging) {
        event->ignore();
        return;
    }
    m_dragging = false;

    const qreal pageW = width() > 0 ? width() : 1;
    int target = m_index;

    if (m_moved && qAbs(m_velocity) > m_flickVelocity) {
        // Flick: turn exactly one page in the flick direction.
        target = m_velocity > 0 ? m_index + 1 : m_index - 1;
    } else {
        // Slow drag: snap to the nearest page.
        target = qRound(m_offset / pageW);
    }

    target = qBound(0, target, m_pages.size() - 1);
    if (target != m_index) {
        m_index = target;
        emit currentIndexChanged(m_index);
    }
    animateToIndex(m_index);
    event->accept();
}
