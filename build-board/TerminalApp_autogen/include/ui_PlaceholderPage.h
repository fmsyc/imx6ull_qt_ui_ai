/********************************************************************************
** Form generated from reading UI file 'PlaceholderPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLACEHOLDERPAGE_H
#define UI_PLACEHOLDERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaceholderPage
{
public:
    QVBoxLayout *rootLayout;
    QHBoxLayout *headerLayout;
    QToolButton *backButton;
    QLabel *titleLabel;
    QSpacerItem *headerSpacer;
    QFrame *contentArea;
    QVBoxLayout *contentLayout;
    QLabel *bodyLabel;

    void setupUi(QWidget *PlaceholderPage)
    {
        if (PlaceholderPage->objectName().isEmpty())
            PlaceholderPage->setObjectName(QString::fromUtf8("PlaceholderPage"));
        PlaceholderPage->resize(1024, 440);
        rootLayout = new QVBoxLayout(PlaceholderPage);
        rootLayout->setSpacing(12);
        rootLayout->setObjectName(QString::fromUtf8("rootLayout"));
        rootLayout->setContentsMargins(24, 16, 24, 16);
        headerLayout = new QHBoxLayout();
        headerLayout->setSpacing(12);
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        backButton = new QToolButton(PlaceholderPage);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        headerLayout->addWidget(backButton);

        titleLabel = new QLabel(PlaceholderPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        headerLayout->addWidget(titleLabel);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(headerSpacer);


        rootLayout->addLayout(headerLayout);

        contentArea = new QFrame(PlaceholderPage);
        contentArea->setObjectName(QString::fromUtf8("contentArea"));
        contentArea->setFrameShape(QFrame::NoFrame);
        contentLayout = new QVBoxLayout(contentArea);
        contentLayout->setObjectName(QString::fromUtf8("contentLayout"));
        bodyLabel = new QLabel(contentArea);
        bodyLabel->setObjectName(QString::fromUtf8("bodyLabel"));
        bodyLabel->setAlignment(Qt::AlignCenter);

        contentLayout->addWidget(bodyLabel);


        rootLayout->addWidget(contentArea);


        retranslateUi(PlaceholderPage);

        QMetaObject::connectSlotsByName(PlaceholderPage);
    } // setupUi

    void retranslateUi(QWidget *PlaceholderPage)
    {
        backButton->setText(QApplication::translate("PlaceholderPage", "\350\277\224\345\233\236", nullptr));
        titleLabel->setText(QApplication::translate("PlaceholderPage", "App", nullptr));
        bodyLabel->setText(QApplication::translate("PlaceholderPage", "\350\277\231\346\230\257\344\270\200\344\270\252\345\215\240\344\275\215\351\241\265\351\235\242\357\274\214\350\257\267\345\234\250\346\255\244\345\244\204\345\256\236\347\216\260\344\275\240\347\232\204 App \347\225\214\351\235\242\343\200\202", nullptr));
        Q_UNUSED(PlaceholderPage);
    } // retranslateUi

};

namespace Ui {
    class PlaceholderPage: public Ui_PlaceholderPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLACEHOLDERPAGE_H
