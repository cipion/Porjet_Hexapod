
#include "PeriodicUpdateTask.h"



/**
 * Classe Decrivant la tache periodique a executer pour la mise a jour des servomoteurs
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 */


    void run()
    {
        Robot.getHandle().sendDirectionsPattes();
    }

