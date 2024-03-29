#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTextEdit>



#include "scan_run.h"
#include <QThread>
#include <QFileDialog>
#include <QDateTime>
#include <qdesktopservices.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    dispatch *dispatch_thread;

    void auto_edit();

    //QThread* main_thread;
    
    qint16 scan_flag=0;

    quint64 t_bar=0;
    quint64 nt_bar=0;

    void output_chuli(QString temp);
    void jindu_chuli(quint16 temp);
    void keyboard_en(bool a);
signals:
    void stop_scan();
    void start_scan();

private:
   Ui::Widget* ui;
};




#endif // WIDGET_H
