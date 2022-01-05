#ifndef SCAN_RUN_H
#define SCAN_RUN_H

#include <QThread>
#include "widget.h"
#include "ui_widget.h"
#include <QTextEdit>
#include <QProgressBar>
#include <QDebug>
#include <QTcpSocket>  //socket



class trytry : public QThread
{
public:

    quint16 *outputbusy;

    quint16 timeout;
    QString ipstr;
    quint32 ipint;
    quint16 *now_thread_num;
    QTextEdit* output_list;

    quint64 *t_bar;
    quint64 *nt_bar;
    QProgressBar* the_bar;
    void run();


};

class dispatch : public QThread
{
    Q_OBJECT
public:

    dispatch();

    quint16 set_thread_num;
    quint16 now_thread_num;
    quint16 timeout;
    quint64 t_bar=0;
    quint64 nt_bar=0;
    quint16 outputbusy=0;
    //QThread* main_thread;
    QTextEdit* ip_list;
    QTextEdit* port_list;
    QTextEdit* output_list;
    QProgressBar* the_bar;
    trytry* try_telnet;

    void tray(const QString& ipstr, quint32 ipint);
    void run();

signals:
    void dispatch_finish();
};




#endif // SCAN_RUN_H
