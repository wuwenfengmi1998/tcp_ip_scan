#ifndef SCAN_RUN_H
#define SCAN_RUN_H

#include <QThread>
#include "ui_widget.h"
#include <QTextEdit>
#include <QProgressBar>
#include <QDebug>
#include <QTcpSocket>  //socket
#include <QLabel>
#include <QPlainTextEdit>



class trytry : public QThread
{
public:

    quint16 *outputbusy;
    quint16 *barbusy;
    quint16 timeout;
    QString ipstr;
    quint32 ipint;
    int *now_thread_num;
    QTextEdit* output_list;

    quint64 *t_bar;
    quint64 *nt_bar;

    void run();


};

class dispatch : public QThread
{
    Q_OBJECT
public:

    dispatch();

    int set_thread_num;
    int now_thread_num;
    int thread_start_lock=0;
    quint16 timeout;
    quint64 *t_bar;
    quint64 *nt_bar;
    quint16 outputbusy=0;
    quint16 barbusy=0;
    //QThread* main_thread;
    QPlainTextEdit* ip_list;
    QPlainTextEdit* port_list;
    QTextEdit* output_list;

    trytry* try_telnet;

    void tray(const QString& ipstr, quint32 ipint);
    void run();

signals:
    void dispatch_finish();
    void dispatch_one();
};




#endif // SCAN_RUN_H
