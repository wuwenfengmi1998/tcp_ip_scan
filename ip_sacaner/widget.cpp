#include "widget.h"
#include "ui_widget.h"








void Widget::jindu_chuli(quint16 temp)
{
    //qDebug()<<temp;
    ui->progressBar->setValue(temp);
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
        connect(dispatch_thread,&dispatch::return_jindu,this,&Widget::jindu_chuli);

        ui->progressBar->setValue(0);
        dispatch_thread->start();
        ui->stard_scan->setDisabled(false);
    });

    connect(this,&Widget::stop_scan,[=]{
        scan_flag=0;
        ui->IP_list->setReadOnly(false);
        ui->port_list->setReadOnly(false);
        ui->timeout->setReadOnly(false);
        ui->threads->setReadOnly(false);
        ui->stard_scan->setText("start scan");

        dispatch_thread->disconnect();
        dispatch_thread->quit();
        dispatch_thread->wait();
        //delete dispatch_thread;
        ui->stard_scan->setDisabled(false);
        qDebug() << "tray_exit";

    });

    connect(ui->stard_scan, &QPushButton::pressed, [=]()
    {
        ui->stard_scan->setDisabled(true);
        if(scan_flag==0)
        {
            emit start_scan();
        }else
        {
            dispatch_thread->terminate();
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


    connect(ui->pushButton_22, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_22->text());

     });
    connect(ui->pushButton_23, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_23->text());

     });
    connect(ui->pushButton_24, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_24->text());

     });
    connect(ui->pushButton_25, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_25->text());

     });
    connect(ui->pushButton_26, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_26->text());

     });
    connect(ui->pushButton_27, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_27->text());

     });
    connect(ui->pushButton_28, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_28->text());

     });
    connect(ui->pushButton_29, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_29->text());

     });
    connect(ui->pushButton_30, &QPushButton::pressed, [=]()
    {

        ui->port_list->appendPlainText(ui->pushButton_30->text());

     });

    connect(ui->pushButton_31, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_31->text());

     });
    connect(ui->pushButton_32, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_32->text());

     });
    connect(ui->pushButton_33, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_33->text());

     });
    connect(ui->pushButton_34, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_34->text());

     });
    connect(ui->pushButton_35, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_35->text());

     });
    connect(ui->pushButton_36, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_36->text());

     });
    connect(ui->pushButton_37, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_37->text());

     });
    connect(ui->pushButton_38, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_38->text());

     });
    connect(ui->pushButton_39, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_39->text());

     });
    connect(ui->pushButton_40, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText("\n");

     });
    connect(ui->pushButton_41, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_41->text());

     });
    connect(ui->pushButton_42, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_42->text());

     });
    connect(ui->pushButton_43, &QPushButton::pressed, [=]()
    {

        ui->port_list->clear();

     });
    connect(ui->pushButton_44, &QPushButton::pressed, [=]()
    {

        ui->port_list->insertPlainText(ui->pushButton_44->text());

     });

}

Widget::~Widget()
{
    //main_thread->exit();
    //delete main_thread;
    delete ui;
}

