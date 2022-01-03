#ifndef SCAN_RUN_H
#define SCAN_RUN_H

#include <QThread>
#include "widget.h"
#include "ui_widget.h"
#include <QTextEdit>
#include <QDebug>
#include <QTcpSocket>  //socket

class scan_run : public QThread
{
public:

    QTextEdit* ip_list;
    QTextEdit* port_list;
    QTextEdit* output_list;

    void tray_scan();
    void ip_scan(const QString& ipstr, quint32 ipint);

protected:
    void run();
};




#endif // SCAN_RUN_H
