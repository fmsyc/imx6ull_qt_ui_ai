/********************************************************************************
** Form generated from reading UI file 'AppTile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPTILE_H
#define UI_APPTILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AppTile
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *iconLabel;
    QLabel *nameLabel;

    void setupUi(QFrame *AppTile)
    {
        if (AppTile->objectName().isEmpty())
            AppTile->setObjectName(QString::fromUtf8("AppTile"));
        AppTile->resize(150, 128);
        AppTile->setMinimumSize(QSize(150, 128));
        AppTile->setMaximumSize(QSize(150, 128));
        AppTile->setCursor(QCursor(Qt::PointingHandCursor));
        AppTile->setFrameShape(QFrame::NoFrame);
        verticalLayout = new QVBoxLayout(AppTile);
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(4, 6, 4, 6);
        iconLabel = new QLabel(AppTile);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        iconLabel->setMinimumSize(QSize(80, 80));
        iconLabel->setMaximumSize(QSize(80, 80));
        iconLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(iconLabel);

        nameLabel = new QLabel(AppTile);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nameLabel);


        retranslateUi(AppTile);

        QMetaObject::connectSlotsByName(AppTile);
    } // setupUi

    void retranslateUi(QFrame *AppTile)
    {
        iconLabel->setText(QString());
        nameLabel->setText(QString());
        Q_UNUSED(AppTile);
    } // retranslateUi

};

namespace Ui {
    class AppTile: public Ui_AppTile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPTILE_H
