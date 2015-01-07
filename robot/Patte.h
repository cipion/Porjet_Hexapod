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

#include "StructPatte.h"
#include "../servomoteur/AX12.h"
#include "../servomoteur/ServoMoteur.h"
#include "../stdrpi/SerialRPi.h"

/**
 * Classe definissant une patte d'un robot contennant 3 servomoteurs (Coxa, Femur, Tibia)
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 * @version 3.1
 */

class Patte {
public:
    /**
     * Constructeur d'un object patte
     *
     * @param liaison
     * 				reference sur la lisaison serie
     * @param step
     * 			valeur du step au depart
     * @param IDCoxa
     * 			ID du servomoteur Coxa de la patte
     * @param IDFemur
     * 			ID du servomoteur Femur de la patte
     * @param IDTibia
     * 			ID du servomoteur Tibia de la patte
     */
    Patte(SerialRPi liaison, int Step, char IDCoxa, char IDFemur, char IDTibia);

    /**
     * Methode de definition des positions des servomoteurs
     *
     * @param PosCoxa
     * 			Position du servomoteur Coxa de la patte de 0 a 0FFF (0 a 1024)
     *
     * @param PosFemur
     * 			Position du servomoteur Femur de la patte de 0 a 0FFF (0 a 1024)
     *
     * @param PosTibia
     * 			Position du servomoteur Tibia de la patte de 0 a 0FFF (0 a 1024)
     */

    ~Patte();

    void setPosAll(char PosCoxa, char PosFemur, char PosTibia);

    /**
     * Methode de definition des positions des servomoteurs en indiquant la vitesse
     *
     * @param PosCoxa
     * 			Position du servomoteur Coxa de la patte de 0 a 0FFF (0 a 1024)
     *
     * @param PosFemur
     * 			Position du servomoteur Femur de la patte de 0 a 0FFF (0 a 1024)
     *
     * @param PosTibia
     * 			Position du servomoteur Tibia de la patte de 0 a 0FFF (0 a 1024)
     *
     * @param vitesse
     * 			Vitesse des servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosAll(char PosCoxa, char PosFemur, char PosTibia, char vitesse);

    /**
     * Methode Pour poser toutes les pattes au sol
     */
    void setGroundAll();

    /**
     * Methode de continuation du mouvement
     *
     * @param angle
     * 			Angle de la droite
     * @param longueur
     * 			Longueur de la droite de mouvement
     *
     * @param vitesse
     * 			Vitesse des servomoteurs
     */
    void upDateDroiteMov(int angle, double longueur, char vitesse);

    /**
     * Methode de definition de la position du servomoteur Femur de la patte
     *
     * @param position
     * 			Angle du servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosCoxa(char position);

    /**
     * Methode de definition de la position du servomoteur Coxa de la patte en indiquant la vitesse
     *
     * @param position
     * 			Angle du servomoteur de 0 a 0FFF (0 a 1024)
     *
     * @param vitesse
     * 			Vitesse du servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosCoxa(char position, char vitesse);

    /**
     * Methode de definition de la position du servomoteur Femur de la patte
     *
     * @param position
     * 			Angle du servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosFemur(char position);


    /**
     * Methode de definition de la position du servomoteur Femur de la patte en indiquant la vitesse
     *
     * @param position
     * 			Angle du servomoteur de 0 a 0FFF (0 a 1024)
     *
     * @param vitesse
     * 			Vitesse du servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosFemur(char position, char vitesse);

    /**
     * Methode de definition de la position du servomoteur Tibia de la patte
     *
     * @param position
     * 			Angle du servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosTibia(char position);

    /**
     * Methode de definition de la position du servomoteur Coxa de la patte en indiquant la vitesse
     *
     * @param position
     * 			Angle du servomoteur de 0 a 0FFF (0 a 1024)
     *
     * @param vitesse
     * 			Vitesse du servomoteur de 0 a 0FFF (0 a 1024)
     */
    void setPosTibia(char position, char vitesse);

    /**
     * Reset de la step courante par celle initiale
     */
    void resetStep();




    /**
     * Methode renvoyant les angles des servomoteurs pour la position middle
     */
    static StructPatte getPointMiddle();

    /**
     * Methode renvoyant les angles des servomoteurs pour la position top
     *
     * @param angle
     * 			Angle de la droite du mouvement
     *
     * @param longueur
     * 			Longueur de la droite du mouvement
     *
     * @return objet structPatte contenant les angles du mouvement pour la position extreme top
     */
    static StructPatte getPointTop(int angle, double longueur);


    /**
     * Methode renvoyant le mouvement a effectuer pour la step courante
     *
     * @param angle
     * 			Angle de la droite du mouvement
     *
     * @param longueur
     * 			Longueur de la droite du mouvement
     *
     * @return objet structPatte contenant les angles du mouvement de la step courante
     */
    StructPatte getPoint(int angle, double longueur);

private:
    int initStep;
    int step;

    ServoMoteur servoCoxa;
    ServoMoteur servoFemur;
    ServoMoteur servoTibia;

    /**
     * Test si l'angle de la droite de mouvement est correct
     *
     * @param angle
     * 				angle de la droite de mouvement
     *
     * @return true si l'angle est correct, flase sinon
     */
   bool testAngle(int angle);

   /**
    * Methode renvoyant le mouvement de la patte en l'air
    *
    * @param position
    * 			Position des servomoteurs
    *
    * @return objet structPatte contenant les angles pour la patte en l'air
    */
   static StructPatte upPatte(StructPatte position);



    /**
     * Test si la longueur de la droite de mouvement est correcte
     *
     * @param longueur
     * 				longueur de la droite de mouvement
     *
     * @return true si la longueur est correct, flase sinon
     */
   bool testLongueur(double longueur);

   /**
    * Methode renvoyant les angles des servomoteurs pour la position top
    *
    * @param angle
    * 			Angle de la droite du mouvement
    *
    * @param longueur
    * 			Longueur de la droite du mouvement
    *
    * @return objet structPatte contenant les angles du mouvement pour la position extreme top
    */
   static StructPatte getPointBottom(int angle, double longueur);


}
