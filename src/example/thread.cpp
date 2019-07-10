#include "thread.h"
#include <QtCore>

Thread::Thread(QObject *parent) : QThread(parent)
{

}

void Thread::run()
{
    for(int i=0; ;i++)
    {

        emit NumberChanged(i);

        this->msleep(130);  //it was 140
    }
}
