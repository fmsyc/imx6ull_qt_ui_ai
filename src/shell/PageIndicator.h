#pragma once
//
// The little "which page am I on" dots below the grid.
// Drawn directly (no QSS) so it stays cheap on the i.MX6ULL.
//
#include <QWidget>

class PageIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit PageIndicator(QWidget *parent = nullptr);

    void setCount(int count);
    void setCurrent(int index);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_count = 0;
    int m_current = 0;
    int m_dotSize = 8;
    int m_spacing = 12;
};
