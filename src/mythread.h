#ifndef MYTHREAD_H

#include <string>

namespace jomt
{
    class MyThread
    {
        std::string _name;

    public:

        MyThread(std::string name):_name{name}{}
        void run();

    };
}
#endif