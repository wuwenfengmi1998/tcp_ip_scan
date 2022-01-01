#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTcpSocket>  //通信套接字


void tray_scan()
{
    qDebug("1");

}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

     qDebug("hello world");

    connect(ui->stard_scan,&QPushButton::pressed,this,tray_scan);//扫描按钮被按下

}

Widget::~Widget()
{
    delete ui;
}

