#include "apps/placeholder/PlaceholderPage.h"
#include "ui_PlaceholderPage.h"

#include "core/AppRegistry.h"

#include <QDebug>

PlaceholderPage::PlaceholderPage(const QString &appId, QWidget *parent)
    : IAppPage(appId, parent)
    , ui(new Ui::PlaceholderPage)
{
    ui->setupUi(this);
    setObjectName(QStringLiteral("PlaceholderPage"));

    connect(ui->backButton, &QToolButton::clicked, this, &IAppPage::requestHome);

    // Resolve the display name from the config so one class can serve many ids.
    QString name = appId;
    if (const AppEntry *entry = AppRegistry::instance().findApp(appId))
        name = entry->name;

    ui->titleLabel->setText(name);
    ui->bodyLabel->setText(QStringLiteral("「%1」是内嵌 App 模板页，请在此实现你的界面。")
                               .arg(name));
}

PlaceholderPage::~PlaceholderPage()
{
    delete ui;
}

void PlaceholderPage::onActivated()
{
    qInfo() << "PlaceholderPage: activated" << appId();
}

void PlaceholderPage::onDeactivated()
{
    qInfo() << "PlaceholderPage: deactivated" << appId();
}
