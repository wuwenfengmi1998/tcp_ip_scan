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
#include <qmath.h>


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

    quint16 set_thread_num;
    quint16 now_thread_num;
    quint16 thread_start_lock=0;
    quint16 timeout;

    QString ip_list;
    QString port_list;




    void run();

signals:
    void dispatch_finish();
    void dispatch_one();
};




#endif // SCAN_RUN_H
