/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextEdit *port_list;
    QLabel *label_3;
    QPushButton *stard_scan;
    QSpinBox *spinBox;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;
    QTextEdit *IP_list;
    QLabel *label;
    QTextEdit *outputlist;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(600, 500);
        Widget->setMinimumSize(QSize(600, 500));
        Widget->setMaximumSize(QSize(600, 500));
        port_list = new QTextEdit(Widget);
        port_list->setObjectName(QString::fromUtf8("port_list"));
        port_list->setGeometry(QRect(500, 100, 91, 111));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(510, 30, 71, 61));
        stard_scan = new QPushButton(Widget);
        stard_scan->setObjectName(QString::fromUtf8("stard_scan"));
        stard_scan->setGeometry(QRect(420, 220, 171, 41));
        spinBox = new QSpinBox(Widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(300, 230, 111, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(999);
        spinBox->setValue(1);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(240, 230, 53, 16));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 230, 53, 16));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 230, 91, 24));
        IP_list = new QTextEdit(Widget);
        IP_list->setObjectName(QString::fromUtf8("IP_list"));
        IP_list->setGeometry(QRect(10, 100, 471, 111));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 141, 71));
        outputlist = new QTextEdit(Widget);
        outputlist->setObjectName(QString::fromUtf8("outputlist"));
        outputlist->setGeometry(QRect(10, 270, 581, 221));
        outputlist->setReadOnly(true);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\350\214\203\345\233\264\n"
"80\n"
"443\n"
"3000-65535", nullptr));
        stard_scan->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\346\211\253\346\217\217", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\347\272\277\347\250\213", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\346\211\253\346\217\217\347\273\223\346\236\234", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\346\211\253\346\217\217\347\273\223\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("Widget", "IP\350\214\203\345\233\264\n"
"127.0.0.1\n"
"0.0.0.0-255.255.255.255\n"
"domain.com", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
