#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

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

#include "../stdrpi/SerialRPi.h"
/**
 * Classe generalise de servomoteur controle par des trames serie
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 * @version 3.1
 */

class ServoMoteur
{
public:
	~ServoMoteur();

    /**
     * Constructeur de l'objet ServoMoteur
     *
     * @param liaison
     * 				Reference de la liaison RS485
     *
     * @param ID
     * 			ID du servomoteur
     */
    ServoMoteur(SerialRPi liaison, char ID);

    /**
     * Methode de positionnement du servomoteur a une vitesse precise
     *
     * @param angleFinal
     * 			angle du servomoteur
     *
     * @param vitesse
     * 			vitesse du servomoteur
     */
    void setPositionExtrapol(char angle, char vitesse);

    /**
     * Methode de positionnement du servomoteur
     *
     * @param angleFinal
     * 			angle du servomoteur
     */
    void setPosition(char angleFinal);


protected:
    SerialRPi serialPi;
    char IDServo;
    /**
     * Methode de controle pour savoir si l'angle du servomoteur est correct
     *
     * @param w_angle
     * 				angle du servomoteur
     *
     * @return 1 si l'angle est correct, 0 sinon
     */
    bool testAngle(char w_angle);

    /**
     * Methode de controle pour savoir si la vitesse du servomoteur est correct
     *
     * @param w_vitesse
     * 				vitesse du servomoteur
     *
     * @return 1 si la vitesse est correct, 0 sinon
     */
    bool testVitesse(char w_vitesse);

    /**
     * Methode permettant de calculer le CRC d'une trame
     *
     * @param data
     * 			Trame de data a envoyer au servomoteur
     *
     * @return le CRC de la trame
     */
    char CalcCRC(char[] data); // probleme tableau de char





};

#endif SERVOMOTEUR_H
