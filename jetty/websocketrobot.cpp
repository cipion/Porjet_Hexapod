#include "websocketrobot.h"

WebSocketRobot::WebSocketRobot()
{
   thread = new std::thread();
   run();
}





/**
     * Thread gestion Websocket Jetty
     */
void WebSocketRobot::run()
{
    thread.join(); // le code est pris en charge par un thread (autre que celui de robot)

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
    thread.detach();
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

