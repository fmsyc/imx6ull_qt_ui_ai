/********************************************************************************
** Form generated from reading UI file 'StatusBar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSBAR_H
#define UI_STATUSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusBar
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *voicePill;
    QHBoxLayout *pillLayout;
    QLabel *micIcon;
    QLabel *hintLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *avatarLabel;
    QLabel *userLabel;
    QLabel *wifiLabel;
    QLabel *signalLabel;
    QLabel *clockLabel;

    void setupUi(QWidget *StatusBar)
    {
        if (StatusBar->objectName().isEmpty())
            StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
        StatusBar->resize(1024, 64);
        StatusBar->setMinimumSize(QSize(0, 64));
        StatusBar->setMaximumSize(QSize(16777215, 64));
        horizontalLayout = new QHBoxLayout(StatusBar);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(24, 10, 24, 10);
        voicePill = new QFrame(StatusBar);
        voicePill->setObjectName(QString::fromUtf8("voicePill"));
        voicePill->setMinimumSize(QSize(320, 40));
        voicePill->setMaximumSize(QSize(340, 40));
        voicePill->setFrameShape(QFrame::Shape::NoFrame);
        pillLayout = new QHBoxLayout(voicePill);
        pillLayout->setSpacing(10);
        pillLayout->setObjectName(QString::fromUtf8("pillLayout"));
        pillLayout->setContentsMargins(14, 4, 14, 4);
        micIcon = new QLabel(voicePill);
        micIcon->setObjectName(QString::fromUtf8("micIcon"));
        micIcon->setMinimumSize(QSize(18, 18));
        micIcon->setMaximumSize(QSize(18, 18));

        pillLayout->addWidget(micIcon);

        hintLabel = new QLabel(voicePill);
        hintLabel->setObjectName(QString::fromUtf8("hintLabel"));

        pillLayout->addWidget(hintLabel);


        horizontalLayout->addWidget(voicePill);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        avatarLabel = new QLabel(StatusBar);
        avatarLabel->setObjectName(QString::fromUtf8("avatarLabel"));
        avatarLabel->setMinimumSize(QSize(28, 28));
        avatarLabel->setMaximumSize(QSize(28, 28));

        horizontalLayout->addWidget(avatarLabel);

        userLabel = new QLabel(StatusBar);
        userLabel->setObjectName(QString::fromUtf8("userLabel"));

        horizontalLayout->addWidget(userLabel);

        wifiLabel = new QLabel(StatusBar);
        wifiLabel->setObjectName(QString::fromUtf8("wifiLabel"));
        wifiLabel->setMinimumSize(QSize(20, 20));
        wifiLabel->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(wifiLabel);

        signalLabel = new QLabel(StatusBar);
        signalLabel->setObjectName(QString::fromUtf8("signalLabel"));
        signalLabel->setMinimumSize(QSize(20, 20));
        signalLabel->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(signalLabel);

        clockLabel = new QLabel(StatusBar);
        clockLabel->setObjectName(QString::fromUtf8("clockLabel"));
        clockLabel->setMinimumSize(QSize(56, 0));
        clockLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(clockLabel);


        retranslateUi(StatusBar);

        QMetaObject::connectSlotsByName(StatusBar);
    } // setupUi

    void retranslateUi(QWidget *StatusBar)
    {
        micIcon->setText(QString());
        hintLabel->setText(QApplication::translate("StatusBar", "\345\214\227\344\272\254\346\254\242\350\277\216\344\275\240", nullptr));
        avatarLabel->setText(QString());
        userLabel->setText(QApplication::translate("StatusBar", "ElniFX", nullptr));
        wifiLabel->setText(QString());
        signalLabel->setText(QString());
        clockLabel->setText(QApplication::translate("StatusBar", "8:24", nullptr));
        Q_UNUSED(StatusBar);
    } // retranslateUi

};

namespace Ui {
    class StatusBar: public Ui_StatusBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSBAR_H
