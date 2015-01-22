#include "robotwebsockethandler.h"





    /**
     * Methode appele lors de la fermeture d'une socket
     *
     * @param statusCode
     * 			code retour de la raison de la fermeture de la socket
     * @param reason
     * 			Message descriptif de la fermeture
     */

    void RobotWebSocketHandler::onClose(int statusCode, String reason) {
        WebSocketRobot.resetRobot();
        std::cout<<"Close: statusCode="<< statusCode << ", reason=" << reason<<std::endl;
    }


    /** Attention :  pas de gestion des erreurs dans ce programme !
     *
     * Methode appele lors d'une erreur du la socket
     *
     * @param t
     * 			exception sur la socket
     *//*
    void RobotWebSocketHandler::onError(Throwable t)
    {
        WebSocketRobot.resetRobot();
        std::cout<<"Error: "<<t.getMessage()<< std::endl;
    }*/

    /**
     * Methode appele lors de la connexion de la socket
     *
     * @param session
     * 			session associe a la socket ouverte avec le client
     */

    void RobotWebSocketHandler::onConnect(Session session)// todo session
    {
        if(!WebSocketRobot.clientIsConnected())
        {
            WebSocketRobot.clientConnect();
            std::cout<<"Connect: " << session.getRemoteAddress().getAddress()<<std::endl; // todo session

            session.getRemote().sendString("OVPIPOD V3.0");//todo session


        }
        else
            session.close();// todo session
    }

    /**
     * Methode appele lors de la reception d'un message du client
     *
     * @param message
     * 			Message envoye par le client
     */
    void RobotWebSocketHandler::onMessage(std::string message) {
        int length (0); // longueur de tableau
        int i (0);

        /**
         * @brief delimiter
         * on separer le message recu pour traitement des information
         */
        std::string delimiter = "[:]";

        size_t pos = 0;
        std::string token;
        while ((pos = message.find(delimiter)) != std::string::npos)
        {
            token = message.substr(0, pos);
            std::cout << token << std::endl;
            message.erase(0, pos + delimiter.length());
        }
         std::String coord[] = message;

         for (i=0; coord[i] =! "\0"; i++)
             length++;

        if(length != 2) // todo longueur tableau
            std::cout<<"MSG : " << message<<std::endl;
        else
            switch(coord[0])
            {
                case "xl":
                    // joystick horizontal gauche
                    Robot.getHandle().MouvementX(std::stoi(coord[1]));
                    break;
                case "yl":
                    // joystick vertical gauche
                    Robot.getHandle().MouvementY(std::stoi(coord[1]));
                    break;
                case "xr":
                    // joystick horizontal droit
                    Robot.getHandle().MouvementZ(std::stoi(coord[1]));
                    break;
                case "yr":
                    // joystick vertical droit
                    //Robot.getHandle().Mouvement?(std::stoi(coord[1]));
                    break;
                case "bt":
                    // boutons gamepads
                    if(std::stoi(coord[1]) == 8)
                    {
                        std::cout<<"RESET Robot"<<std::endl;
                        Robot.getHandle().originRobot();
                    }
                    break;
                case "l2":
                    // gachette gauche
                    break;
                case "r2":
                    // gachette droite
                    break;
                default:
                    std::cout<<"La donnee recu n'est pas un mouvement correct : " << coord[0]<<std::endl;
            }
    }
}
