#include "widget.h"
#include "ui_widget.h"



void Widget::keyboard_en(bool a)
{
    ui->pushButton_2->setDisabled(a);
    ui->pushButton_3->setDisabled(a);
    ui->pushButton_4->setDisabled(a);
    ui->pushButton_5->setDisabled(a);
    ui->pushButton_6->setDisabled(a);
    ui->pushButton_7->setDisabled(a);
    ui->pushButton_8->setDisabled(a);
    ui->pushButton_9->setDisabled(a);
    ui->pushButton_10->setDisabled(a);
    ui->pushButton_11->setDisabled(a);
    ui->pushButton_12->setDisabled(a);
    ui->pushButton_13->setDisabled(a);
    ui->pushButton_14->setDisabled(a);
    ui->pushButton_15->setDisabled(a);
    ui->pushButton_16->setDisabled(a);
    ui->pushButton_17->setDisabled(a);
    ui->pushButton_18->setDisabled(a);
    ui->pushButton_19->setDisabled(a);
    ui->pushButton_21->setDisabled(a);
    ui->pushButton_22->setDisabled(a);
    ui->pushButton_23->setDisabled(a);
    ui->pushButton_24->setDisabled(a);
    ui->pushButton_25->setDisabled(a);
    ui->pushButton_26->setDisabled(a);
    ui->pushButton_27->setDisabled(a);
    ui->pushButton_28->setDisabled(a);
    ui->pushButton_29->setDisabled(a);
    ui->pushButton_30->setDisabled(a);
    ui->pushButton_31->setDisabled(a);
    ui->pushButton_32->setDisabled(a);
    ui->pushButton_33->setDisabled(a);
    ui->pushButton_34->setDisabled(a);
    ui->pushButton_35->setDisabled(a);
    ui->pushButton_36->setDisabled(a);
    ui->pushButton_37->setDisabled(a);
    ui->pushButton_38->setDisabled(a);
    ui->pushButton_39->setDisabled(a);
    ui->pushButton_40->setDisabled(a);
    ui->pushButton_41->setDisabled(a);
    ui->pushButton_42->setDisabled(a);
    ui->pushButton_43->setDisabled(a);
    ui->pushButton_44->setDisabled(a);

    ui->IP_list->setReadOnly(a);
    ui->port_list->setReadOnly(a);
    ui->timeout->setReadOnly(a);
    ui->threads->setReadOnly(a);


}

void Widget::output_chuli(QString temp)
{
    ui->outputlist->append(temp);
}


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
    //ui->stard_scan->setText("start scan");
    ui->IP_list->setPlaceholderText("例子：\n127.0.0.1 - 单IP\n192.168.0.0/24 - 掩码IP段\n0.0.0.0-255.255.255.255 - IP段\ndomain.com - 单域名");
    ui->port_list->setPlaceholderText("例子：\n22 - 单端口\n80;443 - 多个不连续端口\n3000-65535 - 连续的端口范围");


    connect(ui->pushButton_20, &QPushButton::pressed, [=]()
    {
        if(scan_flag==0)
        {
            scan_flag=1;
            keyboard_en(true);
            ui->stard_scan->setDisabled(true);
            ui->pushButton_20->setText("停止Ping");
            dispatch_thread = new dispatch;//线程分发
            dispatch_thread->pingonly=true;
            dispatch_thread->ip_list=ui->IP_list->toPlainText();
            dispatch_thread->port_list=ui->port_list->toPlainText();
            dispatch_thread->set_thread_num = ui->threads->value();
            dispatch_thread->now_thread_num = 0;
            dispatch_thread->timeout = ui->timeout->value();
            connect(dispatch_thread,&dispatch::dispatch_finish,[=]{
                scan_flag=0;
                keyboard_en(false);
                ui->stard_scan->setDisabled(false);
                ui->pushButton_20->setText("仅Ping");
                dispatch_thread->quit();
                //dispatch_thread->wait();
            });
            connect(dispatch_thread,&dispatch::return_jindu,this,&Widget::jindu_chuli,Qt::QueuedConnection);
            connect(dispatch_thread,&dispatch::connect_ok,this,&Widget::output_chuli,Qt::QueuedConnection);
            ui->progressBar->setValue(0);
            dispatch_thread->start();
        }else
        {
            scan_flag=0;
            keyboard_en(false);
            ui->stard_scan->setDisabled(false);
            ui->pushButton_20->setText("仅Ping");
            dispatch_thread->terminate();
            dispatch_thread->quit();
            //dispatch_thread->wait();
        }

     });

    connect(ui->stard_scan, &QPushButton::pressed, [=]()
    {
        if(scan_flag==0)
        {
            scan_flag=1;
            keyboard_en(true);
            ui->pushButton_20->setDisabled(true);
            ui->stard_scan->setText("停止扫描");
            dispatch_thread = new dispatch;//线程分发
            dispatch_thread->pingonly=false;
            dispatch_thread->ip_list=ui->IP_list->toPlainText();
            dispatch_thread->port_list=ui->port_list->toPlainText();
            dispatch_thread->set_thread_num = ui->threads->value();
            dispatch_thread->now_thread_num = 0;
            dispatch_thread->timeout = ui->timeout->value();
            connect(dispatch_thread,&dispatch::dispatch_finish,[=]{
                scan_flag=0;
                keyboard_en(false);
                ui->pushButton_20->setDisabled(false);
                ui->stard_scan->setText("开始扫描");
                dispatch_thread->quit();
                //dispatch_thread->wait();
            });
            connect(dispatch_thread,&dispatch::return_jindu,this,&Widget::jindu_chuli,Qt::QueuedConnection);
            connect(dispatch_thread,&dispatch::connect_ok,this,&Widget::output_chuli,Qt::QueuedConnection);
            ui->progressBar->setValue(0);
            dispatch_thread->start();
        }else
        {
            scan_flag=0;
            keyboard_en(false);
            ui->pushButton_20->setDisabled(false);
            ui->stard_scan->setText("开始扫描");
            dispatch_thread->terminate();
            dispatch_thread->quit();
            //dispatch_thread->wait();
        }

        });//'scan button pass'

    connect(ui->saveoutputbutton, &QPushButton::pressed, [=]()
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("保存文件"), QDir::homePath().append("/iplist-").append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")), tr("文本文件 (*.txt);;所有文件 (*.*)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << ui->outputlist->toPlainText() << endl;
                file.close();
            }
        }

     });

    connect(ui->blog_button, &QPushButton::pressed, [=]()
    {
        QDesktopServices::openUrl(QUrl(QString("https://wnfed.com/").toLatin1()));

     });
    connect(ui->github_button, &QPushButton::pressed, [=]()
    {
        QDesktopServices::openUrl(QUrl(QString("https://github.com/wuwenfengmi1998/tcp_ip_scan").toLatin1()));

     });
    connect(ui->gitlab_button, &QPushButton::pressed, [=]()
    {
        QDesktopServices::openUrl(QUrl(QString("https://git.lmve.net/kevin/tcp_ip_scan").toLatin1()));

     });
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

    connect(ui->clearoutput, &QPushButton::pressed, [=]()
    {

        ui->outputlist->clear();

     });
}

Widget::~Widget()
{
    //main_thread->exit();
    //delete main_thread;
    delete ui;
}

