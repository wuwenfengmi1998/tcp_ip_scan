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

bool Ping(QString strPingIP,qint16 timeout)
{
    QProcess pingProcess;
    QString strArg = "ping " + strPingIP + " -n 2 -w "+QString("%1").arg(timeout);// + " -n 1 -i 2";
    qDebug()<<strArg;
    pingProcess.start(strArg, QIODevice::ReadOnly);
    pingProcess.waitForFinished(-1);
    QString p_stdout = QString::fromLocal8Bit(pingProcess.readAllStandardOutput());
    qDebug()<<p_stdout;
    return p_stdout.contains("TTL=");
}


trytryping::trytryping()
{

}

void trytryping::run()
{
    //emit try_one(1);

    QString ip=this->ipstr;

    if(Ping(ip,this->timeout))
    {
        emit connect_ok(ip);
    }


    //emit try_one(-1);
}


trytry::trytry()
{


}

void trytry::run()
{
    //emit try_one(1);
    QString temp = QString("%1:%2").arg(ipstr).arg(ipint);


    QTcpSocket *m_socket=new QTcpSocket;


    m_socket->connectToHost(ipstr, ipint, QTcpSocket::ReadWrite);
    if(m_socket->waitForConnected(timeout))
    {
        m_socket->disconnectFromHost();
        emit connect_ok(temp);
        qDebug()<<temp;
    }else
    {

    }

    m_socket->flush();
    m_socket->close();

    //m_socket->deleteLater();
    delete m_socket;
    //emit try_one(-1);

}


dispatch::dispatch()
{


}


void dispatch::run()
{
    QStringList str_ip_list = ip_list.split("\n");
    QStringList str_ips_list;
    QStringList str_list_more;
    quint32 ipa,ipb;
    QStringList str_port_list = port_list.split("\n");
    QStringList str_ports_temp;
    QStringList str_porttoport_temp;
    quint32 porta,portb;
    QList <quint32> ports_list;
    quint64 ports_num=0;
    quint64 ips_num=0;
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
            str_ips_list.append(str_ip_list.at(i));
            ips_num+=1;
        }else if(ex_ipv4_more.exactMatch(str_ip_list.at(i)))
        {
            qDebug() << str_ip_list.at(i)<<" is ipv4_more";
            str_list_more=str_ip_list.at(i).split("-");
           ipa=ipv4str_to_int(str_list_more.at(0));
           ipb=ipv4str_to_int(str_list_more.at(1));
           if(ipa>ipb)
           {
                for(;ipb<=ipa;ipb++)
                {
                    str_ips_list.append(ipv4int_to_str(ipb));
                    ips_num+=1;
                }
           }else if(ipb>ipa)
           {
               for(;ipa<=ipb;ipa++)
               {
                   str_ips_list.append(ipv4int_to_str(ipa));
                   ips_num+=1;
               }
           }else//=
           {
               str_ips_list.append(ipv4int_to_str(ipa));
               ips_num+=1;
           }

        }else if(ex_ipv4_more2.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is ipv4_more2";
            str_list_more=str_ip_list.at(i).split("/");
           ipa=ipv4str_to_int(str_list_more.at(0));
           ipb=qPow(2,(32-str_list_more.at(1).toInt()));
           for(quint32 ii=0;ii<ipb;ii++)
           {
               str_ips_list.append(ipv4int_to_str(ipa+ii));
               ips_num+=1;
           }

        }else if(ex_ipv6.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is ipv6";
            str_ips_list.append(str_ip_list.at(i));
            ips_num+=1;
        }else if(ex_domain.exactMatch(str_ip_list.at(i)))
        {

            qDebug() << str_ip_list.at(i)<<" is domain";
            str_ips_list.append(str_ip_list.at(i));
            ips_num+=1;
        }else
        {
            qDebug() << str_ip_list.at(i)<<" don't know what is thit";
        }


     }
    quint64 jindu=0,jindu_old=0;

    if(pingonly)
    {
        for(quint64 ii=0;ii<ips_num;ii++)
        {

            qDebug()<<"int: "<<ii<<" now:"<<this->now_thread_num<<" - set:"<<this->set_thread_num;

            trytry_ping=new trytryping;
            trytry_ping->timeout=this->timeout;
            trytry_ping->ipstr=str_ips_list.at(ii);



            //connect(trytry_ping,&trytryping::try_one,this,&dispatch::f_one);
            //connect(trytry_ping,&trytry::started,this,&dispatch::xiancheng_jia,Qt::QueuedConnection);
            connect(trytry_ping,&trytry::finished,this,&dispatch::xiancheng_jian,Qt::QueuedConnection);
            connect(trytry_ping,&trytryping::connect_ok,[=](QString temp){emit connect_ok(temp);});
            trytry_ping->start();

            jindu=(quint64)(((qreal)(ii)/(qreal)(ips_num))*100);
            jindu+=1;
            if(jindu>100){jindu=100;}
            if(jindu!=jindu_old)
            {
                jindu_old=jindu;
                //qDebug() <<jindu;

                emit return_jindu(jindu);
            }


            this->now_thread_num+=1;
            while(this->now_thread_num>=this->set_thread_num);
        }
    }else
    {
        QRegExp ex_port      ("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
        QRegExp ex_porttoport("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])-(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
        //QRegExp ex_portmore  ("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]);$");
        for (int i = 0; i < str_port_list.size(); ++i)
        {
            str_ports_temp=str_port_list.at(i).split(";");
            for (int ii = 0; ii < str_ports_temp.size(); ++ii)
            {
                if(ex_port.exactMatch(str_ports_temp.at(ii)))
                {
                    qDebug()<<str_ports_temp.at(ii)<<" norlmore port";
                    ports_list.append(str_ports_temp.at(ii).toInt());
                    ports_num+=1;

                }else if(ex_porttoport.exactMatch(str_ports_temp.at(ii)))
                {
                    qDebug()<<str_ports_temp.at(ii)<<" port to port";
                    str_porttoport_temp=str_ports_temp.at(ii).split("-");
                    porta=str_porttoport_temp.at(0).toInt();
                    portb=str_porttoport_temp.at(1).toInt();
                    if(porta>portb)
                    {
                         for(;portb<=porta;portb++)
                         {
                             ports_list.append(portb);
                             ports_num+=1;

                         }
                    }else if(portb>porta)
                    {
                        for(;porta<=portb;porta++)
                        {
                             ports_list.append(porta);
                             ports_num+=1;

                        }
                    }else//=
                    {
                        ports_list.append(porta);
                        ports_num+=1;

                    }
                }

            }

        }

        quint64 scantimes=ips_num*ports_num,now_scan=0;

       qDebug() << "IP: "<<ips_num;
       qDebug() << "port :"<<ports_num;
       qDebug() << "scan times :"<<scantimes;

        for(quint64 ii=0;ii<ips_num;ii++)
        {
            for(quint64 iii=0;iii<ports_num;iii++)
            {

                //qDebug() <<str_ips_list.at(ii)<<":"<< ports_list.at(iii);

                qDebug()<<"int: "<<now_scan<<" now:"<<this->now_thread_num<<" - set:"<<this->set_thread_num;


                connecttry=new trytry;
                connecttry->timeout=this->timeout;
                connecttry->ipstr=str_ips_list.at(ii);
                connecttry->ipint=ports_list.at(iii);


                //connect(connecttry,&trytry::try_one,this,&dispatch::f_one);
                //connect(connecttry,&trytry::started,this,&dispatch::xiancheng_jia,Qt::QueuedConnection);
                connect(connecttry,&trytry::finished,this,&dispatch::xiancheng_jian,Qt::QueuedConnection);
                connect(connecttry,&trytry::connect_ok,[=](QString temp){emit connect_ok(temp);});
                connecttry->start();

                jindu=(quint64)(((qreal)(now_scan)/(qreal)(scantimes))*100);
                jindu+=1;
                if(jindu>100){jindu=100;}
                if(jindu!=jindu_old)
                {
                    jindu_old=jindu;
                    //qDebug() <<jindu;

                    emit return_jindu(jindu);
                }

                now_scan+=1;

                this->now_thread_num+=1;
                while(this->now_thread_num>=this->set_thread_num);

            }


        }
    }






    emit dispatch_finish();
}

void dispatch::f_one(qint16 temp)
{
    this->now_thread_num+=temp;

}

void dispatch::xiancheng_jia()
{
    this->now_thread_num+=1;

}

void dispatch::xiancheng_jian()
{
    this->now_thread_num-=1;

}
