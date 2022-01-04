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
    qDebug() << ipstr<<":"<< ipint;
    *now_thread_num++;
    QTcpSocket m_socket;
    m_socket.connectToHost(ipstr, ipint, QTcpSocket::ReadWrite);
    if (m_socket.waitForConnected(timeout))
    {
        QString temp = QString("%1:%2").arg(ipstr).arg(ipint);
        output_list->append(temp);    
    }
    m_socket.disconnectFromHost();
    m_socket.disconnect();
    *now_thread_num--;
   
}

dispatch::dispatch()
{


}

void dispatch::tray(const QString& ipstr, quint32 ipint)
{

    if (ipint != 0 && ipstr != "")
    {
       
        while (now_thread_num> set_thread_num);

        try_telnet=new trytry;
        try_telnet->ipstr = ipstr;
        try_telnet->ipint = ipint;
        try_telnet->timeout = timeout;
        try_telnet->output_list = output_list;
        try_telnet->now_thread_num = &now_thread_num;
        try_telnet->moveToThread(main_thread);
        try_telnet->start();


    }
}

void dispatch::run()
{
    //qDebug()<< ui->IP_list->toPlainText();


    QTcpSocket* m_socket = new QTcpSocket;

    QStringList str_ip_list = ip_list->toPlainText().split("\n");     //先以行分割
    QStringList str_ips_list;                                              //再以段分割

    QStringList str_port_list = port_list->toPlainText().split("\n");
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
                for (quint32 ii = 0; ii < str_port_list.size(); ii++)//分离端口
                {
                    str_ports_list = str_port_list.at(ii).split("-");
                    if (str_ports_list.size() > 1)
                    {
                        //端口段模式
                        for (quint32 prots = str_ports_list.at(0).toInt(); prots < str_ports_list.at(str_ports_list.size() - 1).toInt() + 1; prots++)
                        {
                            dispatch::tray(ipv4int_to_str(ips), prots);
                        }
                    }
                    else
                    {
                        //单端口模式
                        dispatch::tray(ipv4int_to_str(ips), str_ports_list.at(0).toInt());
                    }
                }
            }
        }
        else
        {
            //单ip或域名模式
            for (quint32 ii = 0; ii < str_port_list.size(); ii++)//分离端口
            {
                str_ports_list = str_port_list.at(ii).split("-");
                if (str_ports_list.size() > 1)
                {
                    //端口段模式
                    for (quint32 prots = str_ports_list.at(0).toInt(); prots < str_ports_list.at(str_ports_list.size() - 1).toInt() + 1; prots++)
                    {
                        dispatch::tray(str_ips_list.at(0), prots);
                    }
                }
                else
                {
                    //单端口模式
                    dispatch::tray(str_ips_list.at(0), str_ports_list.at(0).toInt());

                }
            }

        }



        //for (unsigned long a = str_ips_list.at(0).toInt();a< str_ip_list.size()>1? str_ips_list.at(1).toInt()+1: str_ips_list.at(0).toInt()+1;a++)
        //{
        //    qDebug() << a;
        //}

    }

    //sleep(1);//稍微等一下其他线程完成
    emit dispatch_finish();
}




