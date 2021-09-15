#include"boostlog.h"
#include"mythread.h"

void jomt::MyThread::run()
{
    LT_TRACE << _name << "\tRunning";

    for(int i=0; i<100000; i++)
    {
        if(i%500 == 0)
            LT_INFO << _name << "\tReached a loop of 500 interactions: " << i;
        LT_TRACE << _name << "\tIndex = " << i;
    }
    LT_TRACE << _name << "\tEnd Running";
}
