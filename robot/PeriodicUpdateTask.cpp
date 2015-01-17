
#include "PeriodicUpdateTask.h"



/**
 * Classe Decrivant la tache periodique a executer pour la mise a jour des servomoteurs
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 */

    PeriodicUpdateTask::PeriodicUpdateTask()
    {
        thread = new std::thread();
        run();

    }

    void PeriodicUpdateTask::run()
    {
       thread.join();

       while (1)
       {
           Robot.getHandle().sendDirectionsPattes();
           std::this_thread::sleep_for (std::chrono::milliseconds(1));
       }


       thread.detach();
    }

