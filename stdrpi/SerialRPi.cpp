#include "SerialRPi.h"


SerialRPi::SerialRPi()
{
}


SerialRPi::~SerialRPi()
{
}




SerialRPi::SerialRPi() {
    // Creation de l'instance
    serialPi = SerialFactory.createInstance();

    /*serialPi.addListener(new SerialDataListener() {
            @Override
            public void dataReceived(SerialDataEvent event) {
                // affiche les donnees recu des servomoteurs
                System.out.print(event.getData());
            }
        });*/

    std::cout<<"OPEN_COM_PORT ... "<< std::endl;


        // Ouverture port serie
        serialPi.open(Serial.DEFAULT_COM_PORT, 1000000);



    if(serialPi.isOpen())
        std::cout<<"OK."<< std::endl;
    else
        std::cout<<"KO."<< std::endl;
}

/**
     * Methode permettant d'envoyer un tableau de char
     *
     * @param data
     * 			Tableau de char
     *
     * @param lenght
     * 			Nombre d'octets a envoyer (taille du tableau de char)
     */
void SerialRPi::send(char data[], int lenght) {
    if(serialPi.isOpen()) {
        for(int i = 0; i < lenght; i++) {
            serialPi.write(data[i]);
        }
        serialPi.flush();

        // Attente avant nouvel envoi
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    else {
        std::cout<<"Serie non ouvert"<< std::endl;
    }
}

