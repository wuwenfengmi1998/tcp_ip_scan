#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTcpSocket>  //socket

void Widget::tcp_connected()
{
    qDebug() << "connected";
}


QString ipv4int_to_str(quint32 ipint)
{
    return QString("%1.%2.%3.%4")
        .arg((ipint >> 24) & 0xff)
        .arg((ipint >> 16) & 0xff)
        .arg((ipint >> 8) & 0xff)
        .arg(ipint & 0xff);
}

quint32 ipv4str_to_int(const QString &ipstr)
{
    QStringList ip4 = ipstr.split(".");
    if (ip4.size() == 4)
    {
        return   ip4.at(3).toInt()
            | ip4.at(2).toInt() << 8
            | ip4.at(1).toInt() << 16
            | ip4.at(0).toInt() << 24;
    }
    else
    {
        return 0;
    }
}


void Widget::ip_scan(const QString& ipstr, quint32 ipint)
{
    
    if (ipint != 0 && ipstr!="")
    {
        //qDebug() << ipstr << ":" << ipint;
        QTcpSocket* m_socket=new QTcpSocket(this);
        m_socket->connectToHost(ipstr, ipint, QTcpSocket::ReadWrite);
        connect(m_socket, &QTcpSocket::connected, [=] 
            {
                QString ip = ipstr;// m_socket->peerAddress().toString();
                quint16 port = ipint;// m_socket->peerPort();

                qDebug() << ip << ":" << port;
                QString temp = QString("%1:%2").arg(ip).arg(port);
                ui->outputlist->append(temp);
                m_socket->disconnectFromHost();
                m_socket->disconnect();
                //delete m_socket;

            });

    }
}

void Widget::tray_scan()
{
    //qDebug()<< ui->IP_list->toPlainText();

    
    QTcpSocket* m_socket = new QTcpSocket;

    QStringList str_ip_list = ui->IP_list->toPlainText().split("\n");     //先以行分割
    QStringList str_ips_list;                                              //再以段分割

    QStringList str_port_list = ui->port_list->toPlainText().split("\n");
    QStringList str_ports_list;
    for (int i = 0; i < str_ip_list.size(); ++i)
    {
        //qDebug() << str_ip_list.at(i);
        str_ips_list = str_ip_list.at(i).split("-");
        if (str_ips_list.size() > 1)
        {          
            //ip段模式
            for (quint32 ips = ipv4str_to_int(str_ips_list.at(0)); ips < ipv4str_to_int(str_ips_list.at(str_ips_list.size() - 1)) + 1; ips++)//取出每一个ip
            {
                //qDebug() << ipv4int_to_str(ips);
                for (quint16 ii = 0; ii < str_port_list.size(); ii++)//分离端口
                {
                    str_ports_list = str_port_list.at(ii).split("-");
                    if (str_ports_list.size() > 1)
                    {
                        //端口段模式
                        for (quint16 prots = str_ports_list.at(0).toInt(); prots < str_ports_list.at(str_ports_list.size() - 1).toInt() + 1; prots++)
                        {
                            Widget::ip_scan(ipv4int_to_str(ips), prots);
                        }
                    }
                    else
                    {
                        //单端口模式
                        Widget::ip_scan(ipv4int_to_str(ips), str_ports_list.at(0).toInt());
                    }
                }
            }
        }
        else
        {
            //单ip或域名模式
            for (quint16 ii = 0; ii < str_port_list.size(); ii++)//分离端口
            {
                str_ports_list = str_port_list.at(ii).split("-");
                if (str_ports_list.size() > 1)
                {
                    //端口段模式
                    for (quint16 prots = str_ports_list.at(0).toInt(); prots < str_ports_list.at(str_ports_list.size() - 1).toInt() + 1; prots++)
                    {
                        Widget::ip_scan(str_ips_list.at(0), prots);
                    }
                }
                else
                {
                    //单端口模式
                    Widget::ip_scan(str_ips_list.at(0), str_ports_list.at(0).toInt());

                }
            }
           
        }


        
        //for (unsigned long a = str_ips_list.at(0).toInt();a< str_ip_list.size()>1? str_ips_list.at(1).toInt()+1: str_ips_list.at(0).toInt()+1;a++)
        //{
        //    qDebug() << a;
        //}

    }

   
    
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

    connect(ui->stard_scan,&QPushButton::pressed,this, &Widget::tray_scan);//'scan button pass'
    connect(ui->IP_list,&QTextEdit::textChanged,this, &Widget::auto_edit);

  
}

Widget::~Widget()
{
    delete ui;
}

