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

}

dispatch::dispatch()
{


}


void dispatch::run()
{
    QStringList str_ip_list = ip_list.split("\n");
    QStringList str_ips_list;

    QStringList str_port_list = port_list.split("\n");
    QStringList str_ports_list;

    quint32 ips_num=0;
    quint32 ports_num=0;
    QRegExp ex_ipv4     ("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$");
    QRegExp ex_ipv4_more("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)-((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$");
    QRegExp ex_ipv4_more2("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)/(0?[0-9]|1[0-9]|2[0-9]|3[0-2])$");
    QRegExp ex_ipv6     ("^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$");
    QRegExp ex_domain   ("^([a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.)+[a-zA-Z]{2,}$");


    for (int i = 0; i < str_ip_list.size(); ++i)
    {
        if(ex_ipv4.exactMatch(str_ip_list.at(i)))
        {
            qDebug() << str_ip_list.at(i)<<" is ipv4";
        }else if(ex_ipv4_more.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is ipv4_more";
        }else if(ex_ipv4_more2.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is ipv4_more2";
        }else if(ex_ipv6.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is ipv6";
        }else if(ex_domain.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is domain";
        }else
        {
            qDebug() << str_ip_list.at(i)<<" don't know what is thit";
        }
     }

   qDebug() << ips_num;


    emit dispatch_finish();
}




