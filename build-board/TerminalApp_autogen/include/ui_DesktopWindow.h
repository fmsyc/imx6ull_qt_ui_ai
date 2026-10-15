/********************************************************************************
** Form generated from reading UI file 'DesktopWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESKTOPWINDOW_H
#define UI_DESKTOPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "shell/DockBar.h"
#include "shell/PageIndicator.h"
#include "shell/PagerWidget.h"
#include "shell/StatusBar.h"

QT_BEGIN_NAMESPACE

class Ui_DesktopWindow
{
public:
    QVBoxLayout *rootLayout;
    StatusBar *statusBar;
    QStackedWidget *contentStack;
    QWidget *desktopPage;
    QVBoxLayout *desktopPageLayout;
    PagerWidget *pager;
    PageIndicator *pageIndicator;
    DockBar *dockBar;

    void setupUi(QWidget *DesktopWindow)
    {
        if (DesktopWindow->objectName().isEmpty())
            DesktopWindow->setObjectName(QString::fromUtf8("DesktopWindow"));
        DesktopWindow->resize(1024, 576);
        rootLayout = new QVBoxLayout(DesktopWindow);
        rootLayout->setSpacing(0);
        rootLayout->setObjectName(QString::fromUtf8("rootLayout"));
        rootLayout->setContentsMargins(0, 0, 0, 0);
        statusBar = new StatusBar(DesktopWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        rootLayout->addWidget(statusBar);

        contentStack = new QStackedWidget(DesktopWindow);
        contentStack->setObjectName(QString::fromUtf8("contentStack"));
        desktopPage = new QWidget();
        desktopPage->setObjectName(QString::fromUtf8("desktopPage"));
        desktopPageLayout = new QVBoxLayout(desktopPage);
        desktopPageLayout->setSpacing(0);
        desktopPageLayout->setObjectName(QString::fromUtf8("desktopPageLayout"));
        desktopPageLayout->setContentsMargins(0, 0, 0, 0);
        pager = new PagerWidget(desktopPage);
        pager->setObjectName(QString::fromUtf8("pager"));

        desktopPageLayout->addWidget(pager);

        pageIndicator = new PageIndicator(desktopPage);
        pageIndicator->setObjectName(QString::fromUtf8("pageIndicator"));

        desktopPageLayout->addWidget(pageIndicator);

        contentStack->addWidget(desktopPage);

        rootLayout->addWidget(contentStack);

        dockBar = new DockBar(DesktopWindow);
        dockBar->setObjectName(QString::fromUtf8("dockBar"));

        rootLayout->addWidget(dockBar);


        retranslateUi(DesktopWindow);

        contentStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DesktopWindow);
    } // setupUi

    void retranslateUi(QWidget *DesktopWindow)
    {
        DesktopWindow->setWindowTitle(QApplication::translate("DesktopWindow", "TerminalApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DesktopWindow: public Ui_DesktopWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESKTOPWINDOW_H
