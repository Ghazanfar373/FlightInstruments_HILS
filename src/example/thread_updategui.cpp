#include "thread_updategui.h"
#include <QtCore>

Thread_updateGUI::Thread_updateGUI (QObject *parent) : QThread(parent)
{

}

void Thread_updateGUI::run()
{
    for(int i=0; ;i++)
    {

        emit Number_Changed(i);

        this->msleep(130);  //it was 140
    }
}
