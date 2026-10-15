#include "apps/camera/CameraPage.h"
#include "ui_CameraPage.h"

#include <QDebug>

CameraPage::CameraPage(const QString &appId, QWidget *parent)
    : IAppPage(appId, parent)
    , ui(new Ui::CameraPage)
{
    ui->setupUi(this);
    setObjectName(QStringLiteral("CameraPage"));

    connect(ui->backButton, &QToolButton::clicked, this, &IAppPage::requestHome);

    connect(ui->captureButton, &QPushButton::clicked, this, [this]() {
        ui->statusLabel->setText(QStringLiteral("已拍照（demo）"));
    });
    connect(ui->recordButton, &QPushButton::clicked, this, [this]() {
        m_running = !m_running;
        ui->recordButton->setText(m_running ? QStringLiteral("停止")
                                            : QStringLiteral("录像"));
        ui->statusLabel->setText(m_running ? QStringLiteral("录制中（demo）")
                                           : QStringLiteral("已停止（demo）"));
    });
}

CameraPage::~CameraPage()
{
    delete ui;
}

void CameraPage::onActivated()
{
    // Start the camera / stream here.
    qInfo() << "CameraPage: activated";
    ui->statusLabel->setText(QStringLiteral("准备就绪"));
}

void CameraPage::onDeactivated()
{
    // Stop the camera / stream here to save CPU on the i.MX6ULL.
    qInfo() << "CameraPage: deactivated";
}
