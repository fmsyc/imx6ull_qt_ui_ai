#pragma once
//
// Horizontal, page-snapping swipe container used by the desktop grid.
//
// Design goals on a GPU-less i.MX6ULL:
//   * plain widget geometry moves (no QGraphicsView, no shaders)
//   * short animations (~220 ms) driven by QPropertyAnimation
//   * rubber-band edges + velocity based page flick
//   * works with both mouse and touch (Qt synthesises mouse events from touch)
//
#include <QWidget>

class QPropertyAnimation;

class PagerWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)

public:
    explicit PagerWidget(QWidget *parent = nullptr);

    void addPage(QWidget *page);
    int  pageCount() const { return m_pages.size(); }
    int  currentIndex() const { return m_index; }

    qreal offset() const { return m_offset; }
    void  setOffset(qreal value);

    // Tuning knobs (also configurable from apps.json later if needed).
    void setAnimationDuration(int ms) { m_duration = ms; }
    void setFlickVelocity(qreal pxPerMs) { m_flickVelocity = pxPerMs; }

public slots:
    void setCurrentIndex(int index, bool animate = true);
    void nextPage();
    void prevPage();

signals:
    void currentIndexChanged(int index);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void relayoutPages();
    void animateToIndex(int index);
    qreal maxOffset() const;

    QList<QWidget *> m_pages;
    int   m_index = 0;
    qreal m_offset = 0.0;              // pixels scrolled from page 0

    bool   m_dragging = false;
    bool   m_moved = false;
    int    m_pressX = 0;
    int    m_prevX = 0;
    qreal  m_pressOffset = 0.0;
    qint64 m_lastTime = 0;
    qreal  m_velocity = 0.0;           // px / ms (content velocity)

    int   m_duration = 220;
    qreal m_flickVelocity = 0.35;      // px/ms needed to trigger a page flick
    qreal m_dragThreshold = 6.0;       // px before a press becomes a drag

    QPropertyAnimation *m_anim = nullptr;
};
