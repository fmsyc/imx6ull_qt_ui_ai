/********************************************************************************
** Form generated from reading UI file 'AppPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPPAGE_H
#define UI_APPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppPage
{
public:
    QVBoxLayout *pageLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacerTop;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacerBottom;

    void setupUi(QWidget *AppPage)
    {
        if (AppPage->objectName().isEmpty())
            AppPage->setObjectName(QString::fromUtf8("AppPage"));
        AppPage->resize(1024, 440);
        pageLayout = new QVBoxLayout(AppPage);
        pageLayout->setSpacing(0);
        pageLayout->setObjectName(QString::fromUtf8("pageLayout"));
        pageLayout->setContentsMargins(48, 24, 48, 16);
        titleLabel = new QLabel(AppPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setVisible(false);

        pageLayout->addWidget(titleLabel);

        verticalSpacerTop = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        pageLayout->addItem(verticalSpacerTop);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(22);
        gridLayout->setVerticalSpacing(18);
        gridLayout->setAlignment(Qt::AlignCenter);

        pageLayout->addLayout(gridLayout);

        verticalSpacerBottom = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        pageLayout->addItem(verticalSpacerBottom);


        retranslateUi(AppPage);

        QMetaObject::connectSlotsByName(AppPage);
    } // setupUi

    void retranslateUi(QWidget *AppPage)
    {
        titleLabel->setText(QString());
        Q_UNUSED(AppPage);
    } // retranslateUi

};

namespace Ui {
    class AppPage: public Ui_AppPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPPAGE_H
