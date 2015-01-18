/**
* This file is part of OVPiPod.
*
* OVPiPod is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* OVPiPod is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with OVPiPod.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "../robot/Patte.h"
#include "../robot/PeriodicUpdateTask.h"
#include "../robot/Robot.h"
#include "../robot/StructPatte.h"
#include <iostream>
#include <string>
#include "../jetty/websocketrobot.h"
#include "../libwebsocket/WebSocket.hpp" // lib pour websocket
#include <wiringPi.h> // installer sur le raspberry
#include <wiringSerial.h> // lib pour le GPIO


void helpPrint(); // affichage guide pour choix programme

/**
     * Main de la classe Maitre
     *
     * @param args
     * 			Argument passe en parametre du programme
     */
void hexapod::main(int argc, char *argv[]) {

    int choix = 0;

    if(argc == 1)
    {
        choix = std::stoi(argv[0]);

        if(argv[0] == "-h")
        {
            // Affichage de l'aide
            helpPrint();
        }
    }

    if(choix == 0)
    {
        int sc;
        std::cin >> sc;

        helpPrint();
        choix = sc;
     }

    if(choix != 2) {
        // create gpio controller
        GpioController gpio = GpioFactory.getInstance(); //todo gpio

        // Init du robot et attente instruction
           Robot Hexapod = new Robot(gpio);
    }

    if(choix != 1) {
        // Init serveur websocket
        WebSocketRobot jetty = new WebSocketRobot(); // todo websocket

    }
}

/**
     * Methode affichant l'aide a l'ecran du programme
     */
void helpPrint() {
    std::cout<<"Choix execution :"<< std::endl;
    std::cout<<"\t- 1 : GPIO servomoteur raspberry pi"<< std::endl;
    std::cout<<"\t- 2 : Jetty websocket"<< std::endl;
    std::cout<<"\t- 3 : Lancement total"<< std::endl;
}

