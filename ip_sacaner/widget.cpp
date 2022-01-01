#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTcpSocket>  //通信套接字


void tray_scan()
{
    qDebug("1");

}

void auto_edit()
{
    qDebug("%d",rand());
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

     qDebug("hello world");

    connect(ui->stard_scan,&QPushButton::pressed,this,tray_scan);//扫描按钮被按下
    connect(ui->IP_list,&QTextEdit::textChanged,this,auto_edit);
    connect(ui->IP_list,&QTextEdit::cursorPositionChanged,this,auto_edit);

}

Widget::~Widget()
{
    delete ui;
}

