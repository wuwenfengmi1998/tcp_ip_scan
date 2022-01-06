#include "scan_run.h"


QString ipv4int_to_str(quint32 ipint)
{
    return QString("%1.%2.%3.%4")
        .arg((ipint >> 24) & 0xff)
        .arg((ipint >> 16) & 0xff)
        .arg((ipint >> 8) & 0xff)
        .arg(ipint & 0xff);
}

quint32 ipv4str_to_int(const QString& ipstr)
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

void trytry::run()
{

    if (ipint != 0 && ipstr != "")
    {
        //qDebug()<<ipstr<<":"<<ipint;
        QTcpSocket m_socket;
        m_socket.connectToHost(ipstr, ipint, QTcpSocket::ReadWrite);
        if (m_socket.waitForConnected(timeout))
        {
            while(*outputbusy);
            *outputbusy+=1;
            QString temp = QString("%1:%2").arg(ipstr).arg(ipint);
            output_list->append(temp);
            //qDebug() << ipstr<<":"<< ipint;
            //msleep(1);
            *outputbusy-=1;
        }
        m_socket.disconnectFromHost();
        m_socket.disconnect();


        //while(*barbusy);
        //*barbusy+=1;

        //str.asprintf("停止 %.3f",((0.0+*nt_bar)/(0.0+*t_bar))*100);
        //bt->setText(QString("%1%").arg(((0.0+*nt_bar)/(0.0+*t_bar))*100));
        //qDebug()<<*nt_bar<<"/"<<*t_bar;
        //*barbusy-=1;

        //*now_thread_num-=1;
    }
}

dispatch::dispatch()
{


}

void dispatch::tray(const QString& ipstr, quint32 ipint)
{



    //qDebug()<<"thread "<<now_thread_num<<":"<<set_thread_num;
    while (now_thread_num> set_thread_num)
    {
        //qDebug()<<"while "<<now_thread_num<<":"<<set_thread_num;
    }

    try_telnet=new trytry;
    try_telnet->ipstr = ipstr;
    try_telnet->ipint = ipint;
    try_telnet->timeout = timeout;
    try_telnet->output_list = output_list;


    try_telnet->now_thread_num = &now_thread_num;

    try_telnet->t_bar=t_bar;
    try_telnet->nt_bar=nt_bar;

    try_telnet->outputbusy=&outputbusy;
    try_telnet->barbusy=&barbusy;



    //try_telnet->moveToThread(main_thread);

    connect(try_telnet,&QThread::started,[=]()
    {
        now_thread_num+=1;

        thread_start_lock=0;

    });
    connect(try_telnet,&QThread::finished,[=]()
    {
        now_thread_num-=1;

    });

    while(thread_start_lock);
    try_telnet->start();
    thread_start_lock=1;

    *nt_bar+=1;
    emit dispatch_one();
}

void dispatch::run()
{


    //qDebug()<< ui->IP_list->toPlainText();

    //the_bar->setValue(20);

    //QTcpSocket* m_socket = new QTcpSocket;

    QStringList str_ip_list = ip_list->toPlainText().split("\n");
    QStringList str_ips_list;

    QStringList str_port_list = port_list->toPlainText().split("\n");
    QStringList str_ports_list;



    quint32 ips_num=0;
    quint32 ports_num=0;
    for (int i = 0; i < str_ip_list.size(); ++i)
    {
        //qDebug() << str_ip_list.at(i);
        str_ips_list = str_ip_list.at(i).split("-");
        if (str_ips_list.size() > 1)
        {

            ips_num=ipv4str_to_int(str_ips_list.at(str_ips_list.size() - 1))-ipv4str_to_int(str_ips_list.at(0))+1;
        }else
        {

            ips_num+=1;

        }
     }


    for (quint32 ii = 0; ii < str_port_list.size(); ii++)
    {
        str_ports_list = str_port_list.at(ii).split("-");
        if (str_ports_list.size() > 1)
        {

            ports_num=str_ports_list.at(str_ports_list.size() - 1).toInt() -str_ports_list.at(0).toInt()+1;
        }
        else
        {

            ports_num+=1;
        }
    }

    *t_bar=ips_num*ports_num;
    *nt_bar=0;
    outputbusy=0;

    \
        //qDebug()<<*t_bar;
//*****************************
    for (int i = 0; i < str_ip_list.size(); ++i)
    {
        //qDebug() << str_ip_list.at(i);
        str_ips_list = str_ip_list.at(i).split("-");
        if (str_ips_list.size() > 1)
        {

            for (quint32 ips = ipv4str_to_int(str_ips_list.at(0)); ips < ipv4str_to_int(str_ips_list.at(str_ips_list.size() - 1)) + 1; ips++)
            {
                //qDebug() << ipv4int_to_str(ips);
                for (quint32 ii = 0; ii < str_port_list.size(); ii++)
                {
                    str_ports_list = str_port_list.at(ii).split("-");
                    if (str_ports_list.size() > 1)
                    {

                        for (quint32 prots = str_ports_list.at(0).toInt(); prots < str_ports_list.at(str_ports_list.size() - 1).toInt() + 1; prots++)
                        {
                            dispatch::tray(ipv4int_to_str(ips), prots);
                        }
                    }
                    else
                    {

                        dispatch::tray(ipv4int_to_str(ips), str_ports_list.at(0).toInt());
                    }
                }
            }
        }
        else
        {

            for (quint32 ii = 0; ii < str_port_list.size(); ii++)
            {
                str_ports_list = str_port_list.at(ii).split("-");
                if (str_ports_list.size() > 1)
                {

                    for (quint32 prots = str_ports_list.at(0).toInt(); prots < str_ports_list.at(str_ports_list.size() - 1).toInt() + 1; prots++)
                    {
                        dispatch::tray(str_ips_list.at(0), prots);
                    }
                }
                else
                {

                    dispatch::tray(str_ips_list.at(0), str_ports_list.at(0).toInt());

                }
            }

        }



        //for (unsigned long a = str_ips_list.at(0).toInt();a< str_ip_list.size()>1? str_ips_list.at(1).toInt()+1: str_ips_list.at(0).toInt()+1;a++)
        //{
        //    qDebug() << a;
        //}

    }

    //sleep(1);
    while(now_thread_num);
    emit dispatch_finish();
}




