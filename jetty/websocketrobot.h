#ifndef WEBSOCKETROBOT_H
#define WEBSOCKETROBOT_H

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



#include "../libwebsocket/WebSocket.hpp"
#include "../robot/Robot.h"
#include <thread>

/**
 * Classe Declarant la WebSocket
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 * @version 3.1
 */

class WebSocketRobot
{
public:
    /**
     * @brief WebSocketRobot
     * constructeur qui permet d'instancier un objet thread et appeler la methode run
     */
    WebSocketRobot();

    /**
     * Thread gestion Websocket libwebsocket
     */
    void run();


    /**
     * Methode static pour arreter le robot, et prendre en compte la deconnexion du client
     */
    static void resetRobot();

    /**
     * Methode static pour prendre en compte la connexion d'un client
     */
    static void clientConnect();

    /**
     * Methode static pour savoir si un client est connecte
     */
    static boolean clientIsConnected();



private :
    /**
     * @brief thread
     * On déclare un thread pour gerer les WebSocketRobot
     */
    std::thread thread;


    static bool clientConnected;

};

#endif // WEBSOCKETROBOT_H
