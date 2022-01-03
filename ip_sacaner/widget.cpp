#include "widget.h"
#include "ui_widget.h"








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
    
    QThread* pt;
    pt = new QThread(this);

    scan_run *mt;
    mt = new scan_run;
    mt->ip_list = ui->IP_list;
    mt->port_list = ui->port_list;
    mt->output_list = ui->outputlist;

    mt->moveToThread(pt);
   

    connect(ui->stard_scan, &QPushButton::pressed, [=]() 
        {
            //tray_scan();
            mt->start();
        });//'scan button pass'
    connect(ui->IP_list,&QTextEdit::textChanged,this, &Widget::auto_edit);

  
}

Widget::~Widget()
{
    delete ui;
}

