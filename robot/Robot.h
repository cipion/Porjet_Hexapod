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

#define STEP_MAX = 16;
#define DEAD_ZONE_JOY = 30;
#define OFFSET_ANGLE = 45;
#define LONGUEUR_MAX = 100;
#define VAL_UP_PATTE = 80;
#define VAL_PHI_CIR = 60945;



class Robot
{
public:
	Robot();
	~Robot();

private:
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

       Timer timer;
       long periodTimer;

       char vitesseServomoteurs;

       // Valeurs en INT de -255 a 255 des joysticks
       int x_joy;
       int y_joy;
       int z_joy;

       static Robot handle;

       @SuppressWarnings("unused") // !!!
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
