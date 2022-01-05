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
    



    main_thread = new QThread(this);
    main_thread->start();
    connect(ui->stard_scan, &QPushButton::pressed, [=]() 
        {

            dispatch* dispatch_thread;
            dispatch_thread = new dispatch;

            dispatch_thread->ip_list = ui->IP_list;
            dispatch_thread->port_list = ui->port_list;
            dispatch_thread->output_list = ui->outputlist;
            dispatch_thread->set_thread_num = ui->threads->value();
            dispatch_thread->now_thread_num = 0;
            dispatch_thread->timeout = ui->timeout->value();
            dispatch_thread->the_bar=ui->type_bar;
            dispatch_thread->main_thread = main_thread;
            dispatch_thread->moveToThread(main_thread);
            dispatch_thread->start();
            connect(dispatch_thread, &dispatch::dispatch_finish, [=]()
                {
                    qDebug() << "dispatch_finish";
                    //delete dispatch_thread;
                });
        });//'scan button pass'
    connect(ui->IP_list,&QTextEdit::textChanged,this, &Widget::auto_edit);

  
}

Widget::~Widget()
{
    main_thread->exit();
    //delete main_thread;
    delete ui;
}

