#pragma once
//
// DEMO embedded app. Replace the body with your real camera / V4L2 code.
// It shows the two things every embedded page needs:
//   * a "back" button wired to IAppPage::requestHome()
//   * onActivated()/onDeactivated() hooks for start/stop work
//
#include "apps/IAppPage.h"

namespace Ui { class CameraPage; }

class CameraPage : public IAppPage
{
    Q_OBJECT
public:
    explicit CameraPage(const QString &appId, QWidget *parent = nullptr);
    ~CameraPage() override;

    void onActivated() override;
    void onDeactivated() override;

private:
    Ui::CameraPage *ui;
    bool m_running = false;
};
