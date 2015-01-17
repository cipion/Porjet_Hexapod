#ifndef ROBOTWEBSOCKETHANDLER_H
#define ROBOTWEBSOCKETHANDLER_H


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


/*// todo lib websocket
import org.eclipse.jetty.websocket.api.Session;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketClose;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketConnect;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketError;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketMessage;
import org.eclipse.jetty.websocket.api.annotations.WebSocket;
*/

#include "../robot/Robot.h"
#include <string>
#include "websocketrobot.h"
#include <string>

/**
 * Classe contenant le masquage des methode de la WebSocket
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 * @version 3.1
 */


class RobotWebSocketHandler
{
public:
    RobotWebSocketHandler();

    /**
     * Methode appele lors de la fermeture d'une socket
     *
     * @param statusCode
     * 			code retour de la raison de la fermeture de la socket
     * @param reason
     * 			Message descriptif de la fermeture
     */
    void onClose(int statusCode, String reason);

    /** pas geré en c++
     * Methode appele lors d'une erreur du la socket
     *
     * @param t
     * 			exception sur la socket
     */

    // void onError(Throwable t);

    /**
     * Methode appele lors de la connexion de la socket
     *
     * @param session
     * 			session associe a la socket ouverte avec le client
     */

    void onConnect(Session session); // todo session

    /**
     * Methode appele lors de la reception d'un message du client
     *
     * @param message
     * 			Message envoye par le client
     */
    void onMessage(String message);

};

#endif // ROBOTWEBSOCKETHANDLER_H
