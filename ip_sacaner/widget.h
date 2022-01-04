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


    void auto_edit();

    QThread* main_thread;
    
    
    Ui::Widget* ui;
private:
   
};




#endif // WIDGET_H
