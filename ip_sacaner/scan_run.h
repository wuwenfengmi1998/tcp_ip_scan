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
#include <QFloat16>
#include <QtCore/QProcess>
#include <QMutex>
class trytryping : public QThread
{
    Q_OBJECT
public:
    trytryping();

    quint16 timeout;
    QString ipstr;

    void run();
signals:
    void try_one(qint16);
    void connect_ok(QString);

};

class trytry : public QThread
{
    Q_OBJECT
public:
    trytry();

    quint16 timeout;
    QString ipstr;
    quint32 ipint;
    void run();
signals:
    void try_one(qint16);
    void connect_ok(QString);

};

class dispatch : public QThread
{
    Q_OBJECT
public:

    dispatch();

    qint16 set_thread_num;
    qint16 now_thread_num;
    quint16 thread_start_lock=0;
    quint16 timeout;

    QString ip_list;
    QString port_list;

    trytry *connecttry;
    trytryping *trytry_ping;

    bool pingonly=false;
    void run();
    void f_one(qint16 temp);
    void xiancheng_jia();
    void xiancheng_jian();

signals:
    void dispatch_finish();
    void dispatch_one();
    void return_jindu(quint16);
    void connect_ok(QString);

private:

    QMutex pauseLock;

};




#endif // SCAN_RUN_H
