#ifndef STRUCTPATTE_H
#define STRUCTPATTE_H

#include "Patte.h"
/**
 * Classe StructPatte representant les angles des 3 servomoteurs d'une patte
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 */

class StructPatte {
public:

    /**
     * Constructeur vide de l'objet StructPatte representant les 3 angles des servomoteur de la patte
     * Ce constructeur initialise le mouvement au point milieu
     */
    StructPatte();

    /**
     * Constructeur copy de l'objet StructPatte representant les 3 angles des servomoteur de la patte
     *
     * @param copy
     * 			Structure de l'element a copier
     */
    StructPatte(StructPatte copy); // todo probleme parametre

    /**
     * Constructeur normal de l'objet StructPatte representant les 3 angles des servomoteur de la patte
     *
     * @param AngleCoxa
     * 			Angle du servomoteur Coxa (0 a 1024)
     *
     * @param AngleFemur
     * 			Angle du servomoteur Femur (0 a 1024)
     *
     * @param AngleTibia
     * 			Angle du servomoteur Tibia (0 a 1024)
     */
    StructPatte(char AngleCoxa, char AngleFemur, char AngleTibia);

    /**
     * Getteur angle Coxa de la structure
     *
     * @return angle Coxa
     */
    char getAngleCoxa();

    /**
     * Getteur angle Femur de la structure
     *
     * @return angle Femur
     */
    char getAngleFemur();

    /**
     * Getteur angle Tibia de la structure
     *
     * @return angle Tibia
     */
    char getAngleTibia();

    /**
     * Setteur angle Coxa de la structure
     *
     * @param AngleCoxa
     * 			Angle du servomoteur Coxa
     */
    void setAngleCoxa(char AngleCoxa);

    /**
     * Setteur angle Femur de la structure
     *
     * @param AngleFemur
     * 			Angle du servomoteur Femur
     */
    void setAngleFemur(char AngleFemur);

    /**
     * Setteur angle Tibia de la structure
     *
     * @param AngleTibia
     * 			Angle du servomoteur Tibia
     */
    void setAngleTibia(char AngleTibia);







private:
    char angleCoxa;
    char angleFemur;
    char angleTibia;

};

#endif // STRUCTPATTE_H
