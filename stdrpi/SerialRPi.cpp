#include "SerialRPi.h"


SerialRPi::SerialRPi()
{
}


SerialRPi::~SerialRPi()
{
}




SerialRPi::SerialRPi() {


    /*serialPi.addListener(new SerialDataListener() {
            @Override
            public void dataReceived(SerialDataEvent event) {
                // affiche les donnees recu des servomoteurs
                System.out.print(event.getData());
            }
        });*/

    std::cout<<"OPEN_COM_PORT ... "<< std::endl;


        //initialise wiringPi.
    if (wiringPiSetup () == -1)
    {
      std::cout<< "Unable to start wiringPi:"<< strerror (errno)<<std::endl;
       exit (1);
     }
    else
        std::cout<<"wirringPi start OK"<<std::endl;


        // Ouverture port serie
    if ((fd = serialOpen ("/dev/ttyAMA0", 1000000)) < 0) // TODO déclarer fd
    {
      std::cout<<"Unable to open serial device: "<<strerror (errno)<<std::endl ;

    }
    else
        std::cout<<"serial device : OK."<< std::endl;



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
    if(serialDataAvail (fd)) {  // TODO déclarer fd
        for(int i = 0; i < lenght; i++) {
            serialPutchar (fd, data[i]) ;
        }

        serialFlush (fd); // This discards all data received, or waiting to be send down the given device.

        // Attente avant nouvel envoi

            std::chrono::milliseconds dura (1);
            std::this_thread::sleep_for (dura);// sleep du thread pendant 0,001 sec

    }
    else {
        std::cout<<"Serie non ouvert"<< std::endl;
    }
}

