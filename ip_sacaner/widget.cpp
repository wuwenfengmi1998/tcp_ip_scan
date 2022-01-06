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
    



    //main_thread = new QThread(this);
    //main_thread->start();
    connect(ui->stard_scan, &QPushButton::pressed, [=]() 
        {


        if(scan_flag==0)
        {
            scan_flag=1;

            ui->IP_list->setReadOnly(true);
            ui->port_list->setReadOnly(true);
            ui->timeout->setReadOnly(true);
            ui->threads->setReadOnly(true);
            ui->stard_scan->setText("停止");


            //dispatch* dispatch_thread;
            dispatch_thread = new dispatch;

            dispatch_thread->ip_list = ui->IP_list;
            dispatch_thread->port_list = ui->port_list;
            dispatch_thread->output_list = ui->outputlist;
            dispatch_thread->bt=ui->type_bar;

            dispatch_thread->set_thread_num = ui->threads->value();
            dispatch_thread->now_thread_num = 0;
            dispatch_thread->timeout = ui->timeout->value();

            //dispatch_thread->main_thread = main_thread;
            //dispatch_thread->moveToThread(main_thread);
            dispatch_thread->start();
            connect(dispatch_thread, &dispatch::finished, [=]()
                {
                    qDebug() << "dispatch_finish";
                    ui->IP_list->setReadOnly(false);
                    ui->port_list->setReadOnly(false);
                    ui->timeout->setReadOnly(false);
                    ui->threads->setReadOnly(false);
                    ui->stard_scan->setText("开始扫描");
                    scan_flag=0;

                    disconnect(dispatch_thread);
                    //delete dispatch_thread;
                });
        }else
        {
            qDebug() << "tray_exit";
            dispatch_thread->terminate();

        }

        });//'scan button pass'




    connect(ui->IP_list,&QTextEdit::textChanged,this, &Widget::auto_edit);

  
}

Widget::~Widget()
{
    //main_thread->exit();
    //delete main_thread;
    delete ui;
}

