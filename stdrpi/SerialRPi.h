#ifndef SERIALRPI_H
#define SERIALRPI_H

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






#include <iostream>
#include <wiringPi.h> // installer sur le raspberry
#include <wiringSerial.h> // lib pour le GPIO
#include <chrono>
#include <thread>

/**
 * Classe SerialRPi genere a partir de la lib pi4j
 * http://pi4j.com/example/serial.html
 * Librairie modifie pour accepter une liaison serie de 1Mbit/s
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 * @version 3.1
 */

class SerialRPi
{
public:
    /**
     * Constructeur liaison serie 1 Mbits/s
     */
	SerialRPi();
	~SerialRPi();


    /**
         * Methode permettant d'envoyer un tableau de char
         *
         * @param data
         * 			Tableau de char
         *
         * @param lenght
         * 			Nombre d'octets a envoyer (taille du tableau de char)
         */
    void send(char data[], int lenght);



private:
    //file descriptor
    int fd;
};

#endif SERIALRPI_H
