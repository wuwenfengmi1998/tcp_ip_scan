#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTcpSocket>  //通信套接字

void Widget::tcp_connected()
{
    //qDebug() << "connected";
}

void Widget::tray_scan()
{
    qDebug()<< "try_scan";
    qDebug()<< ui->IP_list->toPlainText();

    //QString text = ui->IP_list->toPlainText();
    QStringList number_list = ui->IP_list->toPlainText().split("\n");
    for (int i = 0; i < number_list.size(); ++i)
    {
        qDebug() << number_list.at(i);
    }

    //QTcpSocket* m_socket = new QTcpSocket;
    //m_socket->connectToHost("127.0.0.1", 58888, QTcpSocket::ReadWrite);
    //connect(m_socket, &QTcpSocket::connected, this, &Widget::tcp_connected);

    
    
}

void Widget::auto_edit()
{
    //qDebug("%d",rand());
}



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

     //qDebug("hello world");

    connect(ui->stard_scan,&QPushButton::pressed,this, &Widget::tray_scan);//扫描按钮被按下
    connect(ui->IP_list,&QTextEdit::textChanged,this, &Widget::auto_edit);

  
}

Widget::~Widget()
{
    delete ui;
}

