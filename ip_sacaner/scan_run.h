#ifndef SCAN_RUN_H
#define SCAN_RUN_H

#include <QThread>


class scan_run : public QThread
{
public:

protected:
    void run();
};

#endif // SCAN_RUN_H
