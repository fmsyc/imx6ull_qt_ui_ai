/********************************************************************************
** Form generated from reading UI file 'mqtt_client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQTT_CLIENT_H
#define UI_MQTT_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mqtt_client
{
public:
    QWidget *widget;
    QTabWidget *tabWidget;
    QWidget *Connect;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_type;
    QLineEdit *lineEdit_type;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ip;
    QLineEdit *lineEdit_ip;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_port;
    QLineEdit *lineEdit_port;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_id;
    QLineEdit *lineEdit_id;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_apply;
    QPushButton *btn_ok;
    QPushButton *btn_cancel;
    QWidget *tab_2;
    QLabel *label_input;
    QComboBox *comboBox;
    QPushButton *btn_add;
    QTextEdit *textEdit_output_context;
    QLabel *label_output;
    QPushButton *btn_public;
    QTextEdit *textEdit_input_title;
    QTextBrowser *textBrowser_publish_info;
    QWidget *tab_3;
    QComboBox *comboBox_2;
    QPushButton *btn_subscribe;
    QTextEdit *textEdit_recContext;
    QLabel *label_context;
    QListWidget *listWidget;
    QLineEdit *lineEdit_listname;
    QListWidget *textEdit_subscribe_name;

    void setupUi(QWidget *mqtt_client)
    {
        if (mqtt_client->objectName().isEmpty())
            mqtt_client->setObjectName(QString::fromUtf8("mqtt_client"));
        mqtt_client->resize(1024, 576);
        widget = new QWidget(mqtt_client);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1024, 576));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"background-color: rgb(154, 153, 150);\n"
"}"));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1021, 581));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        Connect = new QWidget();
        Connect->setObjectName(QString::fromUtf8("Connect"));
        sizePolicy.setHeightForWidth(Connect->sizePolicy().hasHeightForWidth());
        Connect->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(Connect);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 50, 561, 371));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_name = new QLabel(layoutWidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        horizontalLayout->addWidget(label_name);

        lineEdit_name = new QLineEdit(layoutWidget);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        horizontalLayout->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_type = new QLabel(layoutWidget);
        label_type->setObjectName(QString::fromUtf8("label_type"));

        horizontalLayout_2->addWidget(label_type);

        lineEdit_type = new QLineEdit(layoutWidget);
        lineEdit_type->setObjectName(QString::fromUtf8("lineEdit_type"));

        horizontalLayout_2->addWidget(lineEdit_type);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_ip = new QLabel(layoutWidget);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));

        horizontalLayout_3->addWidget(label_ip);

        lineEdit_ip = new QLineEdit(layoutWidget);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));

        horizontalLayout_3->addWidget(lineEdit_ip);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_port = new QLabel(layoutWidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));

        horizontalLayout_4->addWidget(label_port);

        lineEdit_port = new QLineEdit(layoutWidget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));

        horizontalLayout_4->addWidget(lineEdit_port);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_id = new QLabel(layoutWidget);
        label_id->setObjectName(QString::fromUtf8("label_id"));

        horizontalLayout_5->addWidget(label_id);

        lineEdit_id = new QLineEdit(layoutWidget);
        lineEdit_id->setObjectName(QString::fromUtf8("lineEdit_id"));

        horizontalLayout_5->addWidget(lineEdit_id);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);
        layoutWidget1 = new QWidget(Connect);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(760, 60, 211, 331));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_apply = new QPushButton(layoutWidget1);
        btn_apply->setObjectName(QString::fromUtf8("btn_apply"));

        verticalLayout_2->addWidget(btn_apply);

        btn_ok = new QPushButton(layoutWidget1);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        verticalLayout_2->addWidget(btn_ok);

        btn_cancel = new QPushButton(layoutWidget1);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));

        verticalLayout_2->addWidget(btn_cancel);

        tabWidget->addTab(Connect, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_input = new QLabel(tab_2);
        label_input->setObjectName(QString::fromUtf8("label_input"));
        label_input->setGeometry(QRect(20, 90, 121, 18));
        comboBox = new QComboBox(tab_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 30, 321, 26));
        btn_add = new QPushButton(tab_2);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        btn_add->setGeometry(QRect(360, 130, 94, 26));
        textEdit_output_context = new QTextEdit(tab_2);
        textEdit_output_context->setObjectName(QString::fromUtf8("textEdit_output_context"));
        textEdit_output_context->setGeometry(QRect(20, 330, 411, 201));
        label_output = new QLabel(tab_2);
        label_output->setObjectName(QString::fromUtf8("label_output"));
        label_output->setGeometry(QRect(20, 280, 141, 18));
        btn_public = new QPushButton(tab_2);
        btn_public->setObjectName(QString::fromUtf8("btn_public"));
        btn_public->setGeometry(QRect(360, 30, 94, 26));
        textEdit_input_title = new QTextEdit(tab_2);
        textEdit_input_title->setObjectName(QString::fromUtf8("textEdit_input_title"));
        textEdit_input_title->setGeometry(QRect(20, 130, 321, 121));
        textBrowser_publish_info = new QTextBrowser(tab_2);
        textBrowser_publish_info->setObjectName(QString::fromUtf8("textBrowser_publish_info"));
        textBrowser_publish_info->setGeometry(QRect(520, 50, 401, 471));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        comboBox_2 = new QComboBox(tab_3);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(20, 40, 191, 26));
        btn_subscribe = new QPushButton(tab_3);
        btn_subscribe->setObjectName(QString::fromUtf8("btn_subscribe"));
        btn_subscribe->setGeometry(QRect(230, 40, 94, 26));
        textEdit_recContext = new QTextEdit(tab_3);
        textEdit_recContext->setObjectName(QString::fromUtf8("textEdit_recContext"));
        textEdit_recContext->setGeometry(QRect(380, 320, 611, 211));
        label_context = new QLabel(tab_3);
        label_context->setObjectName(QString::fromUtf8("label_context"));
        label_context->setGeometry(QRect(380, 290, 66, 18));
        listWidget = new QListWidget(tab_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(380, 80, 601, 192));
        lineEdit_listname = new QLineEdit(tab_3);
        lineEdit_listname->setObjectName(QString::fromUtf8("lineEdit_listname"));
        lineEdit_listname->setGeometry(QRect(380, 40, 591, 26));
        lineEdit_listname->setFrame(true);
        lineEdit_listname->setReadOnly(true);
        textEdit_subscribe_name = new QListWidget(tab_3);
        textEdit_subscribe_name->setObjectName(QString::fromUtf8("textEdit_subscribe_name"));
        textEdit_subscribe_name->setGeometry(QRect(20, 90, 301, 441));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(mqtt_client);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(mqtt_client);
    } // setupUi

    void retranslateUi(QWidget *mqtt_client)
    {
        mqtt_client->setWindowTitle(QApplication::translate("mqtt_client", "Form", nullptr));
#ifndef QT_NO_WHATSTHIS
        tabWidget->setWhatsThis(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\">Connect</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        Connect->setToolTip(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_name->setText(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\">Name</p></body></html>", nullptr));
        lineEdit_name->setText(QApplication::translate("mqtt_client", "imx6u_client", nullptr));
        label_type->setText(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\">Type</p></body></html>", nullptr));
        lineEdit_type->setText(QApplication::translate("mqtt_client", "MQTT Broker", nullptr));
        label_ip->setText(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\">Broker Address</p></body></html>", nullptr));
        label_port->setText(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\">Broker port</p></body></html>", nullptr));
        label_id->setText(QApplication::translate("mqtt_client", "<html><head/><body><p align=\"center\">Client id</p></body></html>", nullptr));
        btn_apply->setText(QApplication::translate("mqtt_client", "Apply", nullptr));
        btn_ok->setText(QApplication::translate("mqtt_client", "OK", nullptr));
        btn_cancel->setText(QApplication::translate("mqtt_client", "Cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Connect), QApplication::translate("mqtt_client", "Connect", nullptr));
        label_input->setText(QApplication::translate("mqtt_client", "\346\267\273\345\212\240\345\217\221\345\270\203\344\270\273\351\242\230\357\274\232", nullptr));
        btn_add->setText(QApplication::translate("mqtt_client", "\347\241\256\345\256\232", nullptr));
        label_output->setText(QApplication::translate("mqtt_client", "\345\220\221\344\270\273\351\242\230\345\217\221\345\270\203\347\232\204\345\206\205\345\256\271\357\274\232", nullptr));
        btn_public->setText(QApplication::translate("mqtt_client", "\345\217\221\345\270\203", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mqtt_client", "Publish", nullptr));
        btn_subscribe->setText(QApplication::translate("mqtt_client", "\350\256\242\351\230\205", nullptr));
        label_context->setText(QApplication::translate("mqtt_client", "\345\206\205\345\256\271", nullptr));
#ifndef QT_NO_STATUSTIP
        lineEdit_listname->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        lineEdit_listname->setText(QApplication::translate("mqtt_client", "\345\220\215\347\247\260                                              \346\227\266\351\227\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("mqtt_client", "Subscribe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mqtt_client: public Ui_mqtt_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQTT_CLIENT_H
