#ifndef PERIODICUPDATETASK_H
#define PERIODICUPDATETASK_H

#include "Robot.h"
#include <thread>

class PeriodicUpdateTask
{

public:
    PeriodicUpdateTask();

    void run();

private:
    std::thread thread;
};

#endif // PERIODICUPDATETASK_H
