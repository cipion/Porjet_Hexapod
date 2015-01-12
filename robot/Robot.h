#ifndef ROBOT_H
#define ROBOT_H
#pragma once

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
{/* Il faut une librairie pour ça !

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;
import java.util.Timer;
*/}

#include <math.h>
#include "PeriodicUpdateTask"
#include "../stdrpi/SerialRPi.h"
#include "Patte.h"

#define STEP_MAX = 16; // on peut mettre 32 pour plus de fluidité (16 = rapidité)
#define DEAD_ZONE_JOY = 30;
#define OFFSET_ANGLE = 45;
#define LONGUEUR_MAX = 100;
#define VAL_UP_PATTE = 80;
#define VAL_PHI_CIR = 60945;




class Robot
{
public:
    /**
         * Constructeur de l'objet robot representant un ensemble de pattes
         *
         * @param gpioRPi
         * 				Object permettant la manipulation du GPIO du Raspberry Pi
         */
    Robot(GpioController gpioRPi);
    ~Robot();

    /**
         * Methode permettant de parametrer le timer par rapport au module des joysticks
         */
    void processDirectionRobot();

    /**
         * Methode cyclique permettant de mettre a jour les pattes (step + 1)
         */
    void sendDirectionsPattes();

    /**
         * Methode permettant d'obtenir une reference sur l'objet unique Robot
         */
    static Robot getHandle();


    /**
         * Methode permettant de mettre le robot en position de reference
         */
    void originRobot();

    /**
             * Methode permettant de mettre a jour la valeur du joystick gauche sur l'axe horizontal
             *
             * @param x_ws
             * 			Valeur en int (-255 a 255) de la position du joystick gauche sur l'axe horizontal
             */
    void MouvementX(int x_ws);

    /**
                 * Methode permettant de mettre a jour la valeur du joystick gauche sur l'axe vertical
                 *
                 * @param y_ws
                 * 			Valeur en int (-255 a 255) de la position du joystick gauche sur l'axe vertical
                 */
    void MouvementY(int y_ws);

    /**
                     * Methode permettant de mettre a jour la valeur du joystick droit sur l'axe horizontal
                     *
                     * @param z_ws
                     * 			Valeur en int (-255 a 255) de la position du joystick droit sur l'axe horizontal
                     */
    void MouvementZ(int z_ws);








private:

    /**
                         * Methode donnant le maximum des valeurs passe en parametres
                         *
                         * @param val1
                         * 			Valeur 1 a tester
                         *
                         * @param val2
                         * 			Valeur 2 a tester
                         *
                         * @param val3
                         * 			Valeur 3 a tester
                         *
                         * @param val4
                         * 			Valeur 4 a tester
                         *
                         * @param val5
                         * 			Valeur 5 a tester
                         *
                         * @param val6
                         * 			Valeur 6 a tester
                         *
                         * @return la valeur la plus eleve des valeurs passe en parametres
                         */
    static float getMax(float val1, float val2, float val3, float val4, float val5, float val6);

    /**
         * Methode retourant la longueur de la droite de mouvement pour le CIR
         *
         * @param dist
         * 			Distance entre le CIR et la patte
         *
         * @param distMax
         * 			Distance entre le CIR et la patte la plus eloigne
         *
         * @return la valeur de la droite de mouvement
         */
    static int getLongueurMovCIR(float dist, float distMax);


    /**
             * Methode retourant l'angle de la droite de mouvement pour le CIR
             *
             * @param distCIR
             * 			Distance entre le CIR et l'origine du robot
             *
             * @param distHypPatte
             * 			Distance entre le CIR et la patte
             *
             * @param distPatte
             * 			Distance entre la patte et l'origine du robot
             *
             * @return la valeur de l'angle de la droite de mouvement
             */
    static int getAngleCIR(float distCIR, float distHypPatte, float distPatte);

    /**
                 * Methode permettant de retourner un module a partir de deux coordonnees cartesiennes
                 *
                 * @param x
                 * 			Valeur en x de la coordonnee cartesienne
                 *
                 * @param y
                 * 			Valeur en y de la coordonnee cartesienne
                 *
                 * @return module par rapport aux coordonnees
                 */
    static float module(float x, float y);

    /**
                     * Methode permettant de retourner un module a partir de deux coordonnees cartesiennes
                     *
                     * @param x
                     * 			Valeur en x de la coordonnee cartesienne
                     *
                     * @param y
                     * 			Valeur en y de la coordonnee cartesienne
                     *
                     * @return module par rapport aux coordonnees
                     */
    static int module(int x, int y);

    /**
                         * Methode permettant de retourner un angle a partir de deux coordonnees cartesiennes
                         *
                         * @param x
                         * 			Valeur en x de la coordonnee cartesienne
                         *
                         * @param y
                         * 			Valeur en y de la coordonnee cartesienne
                         *
                         * @return Angle en degre par rapport aux coordonnees
                         */
    static int arcTanDeg(int x, int y);



    int angleFL;
    int angleFR;
    int angleML;
    int angleMR;
    int angleBL;
    int angleBR;

    int longueurFL;
    int longueurFR;
    int longueurML;
    int longueurMR;
    int longueurBL;
    int longueurBR;

    // Timer timer; à covertir en c++, pas d'equivalent
    long periodTimer;

    char vitesseServomoteurs;

    // Valeurs en INT de -255 a 255 des joysticks
    int x_joy;
    int y_joy;
    int z_joy;

    static Robot handle;

    // @SuppressWarnings("unused") pour dire en java qu'on ne signale pas le code inutile
    const GpioPinDigitalOutput modeBasc;

    // Definition des pattes pour un Hexapod
    Patte front_left;
    Patte front_right;
    Patte middle_left;
    Patte middle_right;
    Patte back_left;
    Patte back_right;





};

#endif
