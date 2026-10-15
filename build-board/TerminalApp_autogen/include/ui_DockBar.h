/********************************************************************************
** Form generated from reading UI file 'DockBar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKBAR_H
#define UI_DOCKBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockBar
{
public:
    QHBoxLayout *outerLayout;
    QFrame *dockPanel;
    QHBoxLayout *dockLayout;

    void setupUi(QWidget *DockBar)
    {
        if (DockBar->objectName().isEmpty())
            DockBar->setObjectName(QString::fromUtf8("DockBar"));
        DockBar->resize(1024, 84);
        DockBar->setMinimumSize(QSize(0, 84));
        DockBar->setMaximumSize(QSize(16777215, 84));
        outerLayout = new QHBoxLayout(DockBar);
        outerLayout->setSpacing(0);
        outerLayout->setObjectName(QString::fromUtf8("outerLayout"));
        outerLayout->setContentsMargins(16, 0, 16, 8);
        dockPanel = new QFrame(DockBar);
        dockPanel->setObjectName(QString::fromUtf8("dockPanel"));
        dockPanel->setFrameShape(QFrame::NoFrame);
        dockLayout = new QHBoxLayout(dockPanel);
        dockLayout->setSpacing(12);
        dockLayout->setObjectName(QString::fromUtf8("dockLayout"));
        dockLayout->setContentsMargins(28, 6, 28, 6);

        outerLayout->addWidget(dockPanel);


        retranslateUi(DockBar);

        QMetaObject::connectSlotsByName(DockBar);
    } // setupUi

    void retranslateUi(QWidget *DockBar)
    {
        Q_UNUSED(DockBar);
    } // retranslateUi

};

namespace Ui {
    class DockBar: public Ui_DockBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKBAR_H
