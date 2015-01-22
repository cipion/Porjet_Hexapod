#include "websocketrobot.h"

WebSocketRobot::WebSocketRobot()
{
   thread = new std::thread(); // on instancie un objet thread
   run(); // methode pour lancer le serveur et gerer les sockets
}





/**
     * Thread gestion Websocket libwebsocket
     */
void WebSocketRobot::run()
{
    thread.join(); // le code est pris en charge par un thread (autre que celui de robot)

    /* Code à changer avec la nouvelle librairie
     *
    clientConnected = false;
    Server server = new Server(3842); // creation server webSocket port 3842 avec la lib todo
    WebSocketHandler wsHandler = new WebSocketHandler() // objet de manip des webSocket todo
    {

            void configure(WebSocketServletFactory factory) //todo
            {
                factory.register(RobotWebSocketHandler.class); // todo
            }
    };
    server.setHandler(wsHandler); // todo

    server.start(); //todo


    server.join(); // todo

    */

    thread.detach(); // fin du traitement du thread
}

/**
     * Methode static pour arreter le robot, et prendre en compte la deconnexion du client
     */
void WebSocketRobot::resetRobot() {
    clientConnected = false;

    // send origin
    Robot.getHandle().MouvementX(0);
    Robot.getHandle().MouvementY(0);
    Robot.getHandle().MouvementZ(0);
}

/**
     * Methode static pour prendre en compte la connexion d'un client
     */
void WebSocketRobot::clientConnect() {
    clientConnected = true;
}

/**
     * Methode static pour savoir si un client est connecte
     */
bool WebSocketRobot::clientIsConnected() {
    return clientConnected;
}

