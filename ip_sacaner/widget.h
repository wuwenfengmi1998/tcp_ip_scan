#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTextEdit>


#include "scan_run.h"
#include <QThread>

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

    quint64 *t_bar;
    quint64 *nt_bar;


private:
   Ui::Widget* ui;
};




#endif // WIDGET_H
