#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void tray_scan();
    void ip_scan(const QString& ipstr, quint32 ipint);
    void auto_edit();
    void tcp_connected();

    void test();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
