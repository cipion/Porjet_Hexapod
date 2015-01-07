#include "Patte.h"


Patte::~Patte()
{
}

Patte::Patte(SerialRPi liaison, int Step, char IDCoxa, char IDFemur, char IDTibia) {
    initStep = Step;
    step = Step;

    try {
        servoCoxa = new AX12(liaison, IDCoxa);
        servoFemur = new AX12(liaison, IDFemur);
        servoTibia = new AX12(liaison, IDTibia);
    }
    catch(Exception e) {
        System.out.println(e.getMessage());
    }
}

bool Patte::testAngle(int angle) {
    return ( (angle >= 0) && (angle < 360) );
}

bool Patte::testLongueur(double longueur) {
    return ( (longueur >= 0) && (longueur <= Robot.LONGUEUR_MAX) );
}

void Patte::setPosAll(char PosCoxa, char PosFemur, char PosTibia)
{
    setPosCoxa(PosCoxa);
    setPosFemur(PosFemur);
    setPosTibia(PosTibia);
}

void Patte::setPosAll(char PosCoxa, char PosFemur, char PosTibia, char vitesse)
{
    setPosCoxa(PosCoxa, vitesse);
    setPosFemur(PosFemur, vitesse);
    setPosTibia(PosTibia, vitesse);
}

void Patte::setGroundAll() {
    if(step > (Robot.STEP_MAX/2))
        ;// TODO
}

void Patte::upDateDroiteMov(int angle, double longueur, char vitesse)
{
    if(!testAngle(angle))
        throw new Exception("Erreur angle droite mouvement : " + angle);
    if(!testLongueur(longueur))
        throw new Exception("Erreur longueur droite mouvement : " + longueur);

    StructPatte w_position;

    if(longueur != 0)
        w_position = getPoint(angle, longueur);
    else
        w_position = getPointMiddle();

    servoCoxa.setPositionExtrapol(w_position.getAngleCoxa(), vitesse);
    servoFemur.setPositionExtrapol(w_position.getAngleFemur(), vitesse);
    servoTibia.setPositionExtrapol(w_position.getAngleTibia(), vitesse);

    step++;
    if(step > Robot.STEP_MAX)
        step = 0;
}

void Patte::setPosCoxa(char position)
{
    if((position < 405) || (position > 620))
        throw new Exception("Erreur angle servomoteur Coxa : " + (int)position);

    servoCoxa.setPosition(position);
}

void Patte::setPosCoxa(char position, char vitesse)
{
    if((position < 405) || (position > 620))
        throw new Exception("Erreur angle servomoteur Coxa : " + (int)position);

    servoCoxa.setPositionExtrapol(position, vitesse);
}

void Patte::setPosFemur(char position)
{
    if((position < 300) || (position > 700))
        throw new Exception("Erreur angle servomoteur Femur : " + (int)position);

    servoFemur.setPosition(position);
}

void Patte::setPosFemur(char position, char vitesse)
{
    if((position < 300) || (position > 700))
        throw new Exception("Erreur angle servomoteur Coxa : " + (int)position);

    servoFemur.setPositionExtrapol(position, vitesse);
}

void Patte::setPosTibia(char position)
{
    if((position < 220) || (position > 710))
        throw new Exception("Erreur angle servomoteur Tibia : " + (int)position);

    servoTibia.setPosition(position);
}

void Patte::setPosTibia(char position, char vitesse)
{
    if((position < 220) || (position > 710))
        throw new Exception("Erreur angle servomoteur Coxa : " + (int)position);

    servoTibia.setPositionExtrapol(position, vitesse);
}

void Patte::resetStep() {
    step = initStep;
}

 static StructPatte Patte::upPatte(StructPatte position) {
    position.setAngleFemur((char)(position.getAngleFemur() - Robot.VAL_UP_PATTE));
    //position.setAngleTibia((char)(position.getAngleTibia() - Robot.VAL_UP_PATTE));
    return position;
}

static StructPatte Patte::getPointMiddle() {
    return new StructPatte((char)512, (char)575, (char)362);
}

static StructPatte Patte::getPointTop(int angle, double longueur) {
    double longueurDemiCarre = ((longueur / 2) * (longueur / 2));
    double w_dist1 = Math.sqrt( longueurDemiCarre + 19321 - (longueur * 139 * Math.cos(Math.toRadians(angle))) );
    double w_dist2 = Math.sqrt( ((w_dist1 - 52) * (w_dist1 - 52)) + 13225 );

    char angleCoxa;
    if(angle > 180)
        angleCoxa = (char)(512 + (((Math.toDegrees(Math.acos( (((w_dist1 * w_dist1) + 19321 - longueurDemiCarre) / (2 * 139 * w_dist1)) ))) * 256) / 75));
    else
        angleCoxa = (char)(512 - (((Math.toDegrees(Math.acos( (((w_dist1 * w_dist1) + 19321 - longueurDemiCarre) / (2 * 139 * w_dist1)) ))) * 256) / 75));

    char angleFemur = (char)(556 + ((((Math.toDegrees(Math.acos( ((w_dist2 * w_dist2) - 13200) / (134 * w_dist2) )) + Math.toDegrees(Math.acos(115 / w_dist2)) ) - 90) * 256) / 75));
    char angleTibia = (char)(512 - (((138 - Math.toDegrees(Math.acos( (22178 - (w_dist2 * w_dist2)) / 17822 ))) * 256) / 75));

    return new StructPatte(angleCoxa, angleFemur, angleTibia);
}

static Patte::StructPatte getPointBottom(int angle, double longueur) {
    double longueurDemiCarre = ((longueur / 2) * (longueur / 2));
    double w_dist1 = Math.sqrt( longueurDemiCarre + 19321 - (longueur * 139 * Math.cos(Math.toRadians(180-angle))) );
    double w_dist2 = Math.sqrt( ((w_dist1 - 52) * (w_dist1 - 52)) + 13225 );

    char angleCoxa;
    if(angle > 180)
        angleCoxa = (char)(512 - (((Math.toDegrees(Math.acos( (((w_dist1 * w_dist1) + 19321 - longueurDemiCarre) / (2 * 139 * w_dist1)) ))) * 256) / 75));
    else
        angleCoxa = (char)(512 + (((Math.toDegrees(Math.acos( (((w_dist1 * w_dist1) + 19321 - longueurDemiCarre) / (2 * 139 * w_dist1)) ))) * 256) / 75));

    char angleFemur = (char)(556 + ((((Math.toDegrees(Math.acos( ((w_dist2 * w_dist2) - 13200) / (134 * w_dist2) )) + Math.toDegrees(Math.acos(115 / w_dist2)) ) - 90) * 256) / 75));
    char angleTibia = (char)(512 - (((138 - Math.toDegrees(Math.acos( (22178 - (w_dist2 * w_dist2)) / 17822 ))) * 256) / 75));

    return new StructPatte(angleCoxa, angleFemur, angleTibia);
}

StructPatte Patte::getPoint(int angle, double longueur) {
    final int demiStep = (Robot.STEP_MAX/2);
    final int quartStep = (Robot.STEP_MAX/4);
    int w_step = Math.abs(step - demiStep);
    StructPatte w_middle = getPointMiddle();
    StructPatte w_extrem;

    if(w_step < quartStep)
    {
        w_extrem = getPointTop(angle, longueur);
    }
    else if(w_step > quartStep)
    {
        w_step = demiStep - w_step;
        w_extrem = getPointBottom(angle, longueur);
    }
    else
    {
        if((step > demiStep) && (step < Robot.STEP_MAX))
            return upPatte(w_middle);
        else
            return w_middle;
    }

    StructPatte w_position = new StructPatte((char)( (((quartStep - w_step) * w_extrem.getAngleCoxa()) + (w_step * w_middle.getAngleCoxa())) / quartStep ),
            (char)( (((quartStep - w_step) * w_extrem.getAngleFemur()) + (w_step * w_middle.getAngleFemur())) / quartStep ),
            (char)( (((quartStep - w_step) * w_extrem.getAngleTibia()) + (w_step * w_middle.getAngleTibia())) / quartStep ));

    // On leve la patte pour pisser
    if((step > demiStep) && (step < Robot.STEP_MAX))
        w_position = upPatte(w_position);

    return w_position;
}
