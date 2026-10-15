/********************************************************************************
** Form generated from reading UI file 'CameraPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPAGE_H
#define UI_CAMERAPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraPage
{
public:
    QVBoxLayout *rootLayout;
    QHBoxLayout *headerLayout;
    QToolButton *backButton;
    QLabel *titleLabel;
    QSpacerItem *headerSpacer;
    QFrame *videoArea;
    QVBoxLayout *videoLayout;
    QLabel *videoHint;
    QHBoxLayout *controlLayout;
    QPushButton *captureButton;
    QPushButton *recordButton;
    QSpacerItem *controlSpacer;
    QLabel *statusLabel;

    void setupUi(QWidget *CameraPage)
    {
        if (CameraPage->objectName().isEmpty())
            CameraPage->setObjectName(QString::fromUtf8("CameraPage"));
        CameraPage->resize(1024, 440);
        rootLayout = new QVBoxLayout(CameraPage);
        rootLayout->setSpacing(12);
        rootLayout->setObjectName(QString::fromUtf8("rootLayout"));
        rootLayout->setContentsMargins(24, 16, 24, 16);
        headerLayout = new QHBoxLayout();
        headerLayout->setSpacing(12);
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        backButton = new QToolButton(CameraPage);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        headerLayout->addWidget(backButton);

        titleLabel = new QLabel(CameraPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        headerLayout->addWidget(titleLabel);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(headerSpacer);


        rootLayout->addLayout(headerLayout);

        videoArea = new QFrame(CameraPage);
        videoArea->setObjectName(QString::fromUtf8("videoArea"));
        videoArea->setFrameShape(QFrame::NoFrame);
        videoArea->setFrameShadow(QFrame::Plain);
        videoLayout = new QVBoxLayout(videoArea);
        videoLayout->setObjectName(QString::fromUtf8("videoLayout"));
        videoHint = new QLabel(videoArea);
        videoHint->setObjectName(QString::fromUtf8("videoHint"));
        videoHint->setAlignment(Qt::AlignCenter);

        videoLayout->addWidget(videoHint);


        rootLayout->addWidget(videoArea);

        controlLayout = new QHBoxLayout();
        controlLayout->setSpacing(12);
        controlLayout->setObjectName(QString::fromUtf8("controlLayout"));
        captureButton = new QPushButton(CameraPage);
        captureButton->setObjectName(QString::fromUtf8("captureButton"));

        controlLayout->addWidget(captureButton);

        recordButton = new QPushButton(CameraPage);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));

        controlLayout->addWidget(recordButton);

        controlSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controlLayout->addItem(controlSpacer);

        statusLabel = new QLabel(CameraPage);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        controlLayout->addWidget(statusLabel);


        rootLayout->addLayout(controlLayout);


        retranslateUi(CameraPage);

        QMetaObject::connectSlotsByName(CameraPage);
    } // setupUi

    void retranslateUi(QWidget *CameraPage)
    {
        backButton->setText(QApplication::translate("CameraPage", "\350\277\224\345\233\236", nullptr));
        titleLabel->setText(QApplication::translate("CameraPage", "\346\221\204\345\203\217\345\244\264", nullptr));
        videoHint->setText(QApplication::translate("CameraPage", "\350\247\206\351\242\221\351\242\204\350\247\210\345\214\272\345\237\237\357\274\210\345\234\250\346\255\244\345\244\204\346\224\276\344\275\240\347\232\204\346\221\204\345\203\217\345\244\264 / \346\222\255\346\224\276\345\231\250\346\216\247\344\273\266\357\274\211", nullptr));
        captureButton->setText(QApplication::translate("CameraPage", "\346\213\215\347\205\247", nullptr));
        recordButton->setText(QApplication::translate("CameraPage", "\345\275\225\345\203\217", nullptr));
        statusLabel->setText(QString());
        Q_UNUSED(CameraPage);
    } // retranslateUi

};

namespace Ui {
    class CameraPage: public Ui_CameraPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPAGE_H
