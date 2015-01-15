#include "websocketrobot.h"

WebSocketRobot::WebSocketRobot()
{
}





    /**
     * Thread gestion Websocket Jetty
     */
    public void run()
    {
        clientConnected = false;
        Server server = new Server(3842);
        WebSocketHandler wsHandler = new WebSocketHandler()
        {
            @Override
            public void configure(WebSocketServletFactory factory)
            {
                factory.register(RobotWebSocketHandler.class);
            }
        };
        server.setHandler(wsHandler);
        try
        {
            server.start();
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        try {
            server.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    /**
     * Methode static pour arreter le robot, et prendre en compte la deconnexion du client
     */
    public static void resetRobot() {
        clientConnected = false;

        // send origin
        Robot.getHandle().MouvementX(0);
        Robot.getHandle().MouvementY(0);
        Robot.getHandle().MouvementZ(0);
    }

    /**
     * Methode static pour prendre en compte la connexion d'un client
     */
    public static void clientConnect() {
        clientConnected = true;
    }

    /**
     * Methode static pour savoir si un client est connecte
     */
    public static boolean clientIsConnected() {
        return clientConnected;
    }

