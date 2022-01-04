#ifndef SCAN_RUN_H
#define SCAN_RUN_H

#include <QThread>
#include "widget.h"
#include "ui_widget.h"
#include <QTextEdit>
#include <QDebug>
#include <QTcpSocket>  //socket


class trytry : public QThread
{
public:


    quint16 timeout;
    QString ipstr;
    quint32 ipint;
    QTextEdit* output_list;
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


    QThread* main_thread;
    QTextEdit* ip_list;
    QTextEdit* port_list;
    QTextEdit* output_list;

    void tray(const QString& ipstr, quint32 ipint);
    void run();

signals:
    void dispatch_finish();
};




#endif // SCAN_RUN_H
