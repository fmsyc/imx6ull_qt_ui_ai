#pragma once
//
// A generic embedded page. It reads its display name from config/apps.json via
// the app id, which lets several app ids share one implementation.
//
// Use it as a scaffold: copy this folder, rename, and replace the body.
//
#include "apps/IAppPage.h"

namespace Ui { class PlaceholderPage; }

class PlaceholderPage : public IAppPage
{
    Q_OBJECT
public:
    explicit PlaceholderPage(const QString &appId, QWidget *parent = nullptr);
    ~PlaceholderPage() override;

    void onActivated() override;
    void onDeactivated() override;

private:
    Ui::PlaceholderPage *ui;
};
