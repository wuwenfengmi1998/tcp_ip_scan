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

    ui->outputlist->setReadOnly(true);
    ui->stard_scan->setText("start scan");

    connect(this,&Widget::start_scan,[=]{
        scan_flag=1;
        ui->IP_list->setReadOnly(true);
        ui->port_list->setReadOnly(true);
        ui->timeout->setReadOnly(true);
        ui->threads->setReadOnly(true);
        ui->stard_scan->setText("stop scan");
        dispatch_thread = new dispatch;//线程分发
        dispatch_thread->ip_list=ui->IP_list->toPlainText();
        dispatch_thread->port_list=ui->port_list->toPlainText();
        dispatch_thread->set_thread_num = ui->threads->value();
        dispatch_thread->now_thread_num = 0;
        dispatch_thread->timeout = ui->timeout->value();
        connect(dispatch_thread,&dispatch::dispatch_finish,[=]{
           emit stop_scan();
        });
        dispatch_thread->start();

    });

    connect(this,&Widget::stop_scan,[=]{
        scan_flag=0;
        ui->IP_list->setReadOnly(false);
        ui->port_list->setReadOnly(false);
        ui->timeout->setReadOnly(false);
        ui->threads->setReadOnly(false);
        ui->stard_scan->setText("start scan");
        qDebug() << "tray_exit";
        dispatch_thread->disconnect();
        dispatch_thread->terminate();
        delete dispatch_thread;

    });

    connect(ui->stard_scan, &QPushButton::pressed, [=]()
    {
        if(scan_flag==0)
        {
            emit start_scan();
        }else
        {
           emit stop_scan();

        }

        });//'scan button pass'


    connect(ui->pushButton_2, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_2->text());
     });
    connect(ui->pushButton_3, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_3->text());
     });
    connect(ui->pushButton_4, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_4->text());
     });
    connect(ui->pushButton_5, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_5->text());
     });
    connect(ui->pushButton_6, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText("\n");
     });
    connect(ui->pushButton_7, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_7->text());
     });
    connect(ui->pushButton_8, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_8->text());
     });
    connect(ui->pushButton_9, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_9->text());
     });
    connect(ui->pushButton_10, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_10->text());
     });
    connect(ui->pushButton_11, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_11->text());
     });
    connect(ui->pushButton_12, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_12->text());
     });
    connect(ui->pushButton_13, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_13->text());
     });
    connect(ui->pushButton_14, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_14->text());
     });
    connect(ui->pushButton_15, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_15->text());
     });
    connect(ui->pushButton_16, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_16->text());
     });
    connect(ui->pushButton_17, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_17->text());
     });
    connect(ui->pushButton_18, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_18->text());
     });
    connect(ui->pushButton_19, &QPushButton::pressed, [=]()
    {

        ui->IP_list->insertPlainText(ui->pushButton_19->text());
     });
    connect(ui->pushButton_21, &QPushButton::pressed, [=]()
    {

        ui->IP_list->clear();
     });
}

Widget::~Widget()
{
    //main_thread->exit();
    //delete main_thread;
    delete ui;
}

