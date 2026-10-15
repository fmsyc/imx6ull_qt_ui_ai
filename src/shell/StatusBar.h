#pragma once
//
// Top status bar: voice-assistant pill on the left, user + connectivity + clock
// on the right. Purely informational for now; hook up real data as needed.
//
#include <QWidget>

class QTimer;

namespace Ui { class StatusBar; }

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar() override;

    void setHintText(const QString &text);
    void setUserName(const QString &name);

private slots:
    void updateClock();

private:
    Ui::StatusBar *ui;
    QTimer *m_clockTimer;
};
