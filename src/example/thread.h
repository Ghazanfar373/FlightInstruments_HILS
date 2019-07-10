#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <my_parameters.h>

class Thread : public QThread
{
    Q_OBJECT


public:
    explicit Thread(QObject *parent = 0);
    void run();
    bool stop;
   // My_Parameters pp;
signals:
    int NumberChanged(int);

public slots:

};

#endif // THREAD_H
