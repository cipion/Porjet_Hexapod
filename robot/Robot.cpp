#include "Robot.h"
#define M_Pi 3.14159265359

Robot::Robot(GpioController gpioRPi)
{
    // Ouverture COM serie avant creation des pattes
            SerialRPi liaisonRS232 = new SerialRPi();

            // Positionnement bascule mode emission
            modeBasc = gpioRPi.provisionDigitalOutputPin(RaspiPin.GPIO_01, PinState.HIGH);//todo gpio


                Thread.sleep(1000); // trouver un equivalent en C++ todo


            // Creation des pattes de l'hexapod
            front_left = new Patte(liaisonRS232, (STEP_MAX/4), (char)1, (char)3, (char)5);
            front_right = new Patte(liaisonRS232, ((STEP_MAX/4)*3), (char)2, (char)4, (char)6);
            middle_left = new Patte(liaisonRS232, ((STEP_MAX/4)*3), (char)13, (char)15, (char)17);
            middle_right = new Patte(liaisonRS232, (STEP_MAX/4), (char)14, (char)16, (char)18);
            back_left = new Patte(liaisonRS232, (STEP_MAX/4), (char)7, (char)9, (char)11);
            back_right = new Patte(liaisonRS232, ((STEP_MAX/4)*3), (char)8, (char)10, (char)12);

            std::cout<<"InitServo ..."<<std::endl;

            // Init Servomoteurs
            originRobot();


            Thread.sleep(200); // sleep 0,2 seconde todo


            std::cout<<"OK"<<std::endl;

            // Definition de l'handle
            handle = this;

            periodTimer = 0;
            vitesseServomoteurs = 512;
}


Robot::~Robot()
{
    delete front_left;
    delete front_right;
    delete middle_left;
    delete middle_right;
    delete back_left;
    delete back_right;
}


void Robot::processDirectionRobot()
{
    long w_periodTimer = 100;
            // Set du timer appellant la methode sendDirectionsPattes cycliquement

            int w_x = x_joy;
            int w_y = y_joy;
            int w_z = z_joy;

            //System.out.println("val coord : " + w_x + ", " + w_y + ", " + w_z);

            int moduleLeftJoy = module(w_x, w_y);
            int angleLeftJoy = arcTanDeg(w_x, w_y);

            if(moduleLeftJoy <= 120)
            {
                w_periodTimer = 120;
                vitesseServomoteurs = 128;
            }
            else if(moduleLeftJoy <= 200)
            {
                w_periodTimer = 60;
                vitesseServomoteurs = 256;
            }
            else
            {
                w_periodTimer = 30;
                vitesseServomoteurs = 670;
            }

            if(w_z == 0)
            {
                if( (w_x != 0) || (w_y != 0) )
                {
                    // Mouvement sans CIR
                    angleFL		= (angleLeftJoy + OFFSET_ANGLE) % 360;
                    longueurFL	= LONGUEUR_MAX;

                    angleFR		= (angleLeftJoy - OFFSET_ANGLE + 180) % 360;
                    longueurFR	= LONGUEUR_MAX;

                    angleML		= angleLeftJoy;
                    longueurML	= LONGUEUR_MAX;

                    angleMR		= (angleLeftJoy + 180) % 360;
                    longueurMR	= LONGUEUR_MAX;

                    angleBL		= ((angleLeftJoy - OFFSET_ANGLE) + 360) % 360;
                    longueurBL	= LONGUEUR_MAX;

                    angleBR		= (angleLeftJoy + OFFSET_ANGLE + 180) % 360;
                    longueurBR	= LONGUEUR_MAX;
                }
                else
                    w_periodTimer = 0;
            }
            else
            {
                if((w_x != 0) || (w_y != 0))
                {
                    int w_phiCIR;
                    int w_signJoyLeft;

                    if(w_z > 0)
                    {
                        w_phiCIR = 90;
                        w_signJoyLeft = -1;
                    }
                    else
                    {
                        w_phiCIR = -90;
                        w_signJoyLeft = 1;
                    }


                    float w_xCIR = round( ( (cos(M_Pi * ( angleLeftJoy + w_phiCIR )/180) * VAL_PHI_CIR ) / (w_signJoyLeft * w_z)) * 100) / 100;
                    float w_yCIR = round( ( (sin(M_Pi * ( angleLeftJoy + w_phiCIR )/180) * VAL_PHI_CIR ) / (w_signJoyLeft * w_z)) * 100) / 100;

                    float w_distCIR = module(w_xCIR, w_yCIR);

                    // Calcul distances (toujour positif)
                    float w_distFL = (float)sqrt( ((158 + w_xCIR) * (158 + w_xCIR)) + ((218 - w_yCIR) * (218 - w_yCIR)) );
                    float w_distFR = (float)sqrt( ((158 - w_xCIR) * (158 - w_xCIR)) + ((218 - w_yCIR) * (218 - w_yCIR)) );
                    float w_distML = (float)sqrt( ((239 + w_xCIR) * (239 + w_xCIR)) + (w_yCIR * w_yCIR) );
                    float w_distMR = (float)sqrt( ((239 - w_xCIR) * (239 - w_xCIR)) + (w_yCIR * w_yCIR) );
                    float w_distBL = (float)sqrt( ((158 + w_xCIR) * (158 + w_xCIR)) + ((218 + w_yCIR) * (218 + w_yCIR)) );
                    float w_distBR = (float)sqrt( ((158 - w_xCIR) * (158 - w_xCIR)) + ((218 + w_yCIR) * (218 + w_yCIR)) );

                    float w_distMax = getMax(w_distFL, w_distFR, w_distML, w_distMR, w_distBL, w_distBR);

                    angleFL		= (angleLeftJoy + (w_signJoyLeft * getAngleCIR(w_distCIR, w_distFL, (float)269.235956)) + OFFSET_ANGLE + 360) % 360;
                    longueurFL	= getLongueurMovCIR(w_distFL, w_distMax);

                    angleFR		= (angleLeftJoy + (w_signJoyLeft * getAngleCIR(w_distCIR, w_distFR, (float)269.235956)) - OFFSET_ANGLE + 180) % 360;
                    longueurFR	= getLongueurMovCIR(w_distFR, w_distMax);

                    angleML		= (angleLeftJoy + (w_signJoyLeft * getAngleCIR(w_distCIR, w_distML, (float)239)) + 360) % 360;
                    longueurML	= getLongueurMovCIR(w_distML, w_distMax);

                    angleMR		= (angleLeftJoy + (w_signJoyLeft * getAngleCIR(w_distCIR, w_distMR, (float)239)) + 180) % 360;
                    longueurMR	= getLongueurMovCIR(w_distMR, w_distMax);

                    angleBL		= ((angleLeftJoy + (w_signJoyLeft * getAngleCIR(w_distCIR, w_distBL, (float)269.235956)) - OFFSET_ANGLE) + 360) % 360;
                    longueurBL	= getLongueurMovCIR(w_distBL, w_distMax);

                    angleBR		= (angleLeftJoy + (w_signJoyLeft * getAngleCIR(w_distCIR, w_distBR, (float)269.235956)) + OFFSET_ANGLE + 180) % 360;
                    longueurBR	= getLongueurMovCIR(w_distBR, w_distMax);
                }
                else
                {
                    int offsetAngleCIR = 0;

                    if(w_z > 0)
                        offsetAngleCIR = 180;

                    angleFL		= 225 - offsetAngleCIR;
                    longueurFL	= LONGUEUR_MAX;

                    angleFR		= 315 - offsetAngleCIR;
                    longueurFR	= LONGUEUR_MAX;

                    angleML		= 270 - offsetAngleCIR;
                    longueurML	= getLongueurMovCIR((float)239, (float)269.235956);

                    angleMR		= 270 - offsetAngleCIR;
                    longueurMR	= getLongueurMovCIR((float)239, (float)269.235956);

                    angleBL		= 315 - offsetAngleCIR;
                    longueurBL	= LONGUEUR_MAX;

                    angleBR		= 225 - offsetAngleCIR;
                    longueurBR	= LONGUEUR_MAX;

                    if((w_z > 180) || (w_z < -180))
                    {
                        w_periodTimer = 120;
                        vitesseServomoteurs = 128;
                    }
                    else
                    {
                        w_periodTimer = 50;
                        vitesseServomoteurs = 384;
                    }
                }
            }

            if(w_periodTimer != periodTimer)
            {
                if(periodTimer != 0)
                    timer.cancel();//todo timer

                if(w_periodTimer != 0)
                {
                    timer = new Timer(); // todo
                    timer.schedule(new PeriodicUpdateTask(), 0, w_periodTimer);//todo
                }

                periodTimer = w_periodTimer;
            }
}


void Robot::sendDirectionsPattes()
{
    // Mise a jour des patte
            if( (x_joy == 0) && (y_joy == 0) && (z_joy == 0) )
            {
                // baisser toute les pattes
            }
            else
            {

                    front_left.upDateDroiteMov(angleFL, longueurFL, vitesseServomoteurs);
                    front_right.upDateDroiteMov(angleFR, longueurFR, vitesseServomoteurs);
                    middle_left.upDateDroiteMov(angleML, longueurML, vitesseServomoteurs);
                    middle_right.upDateDroiteMov(angleMR, longueurMR, vitesseServomoteurs);
                    back_left.upDateDroiteMov(angleBL, longueurBL, vitesseServomoteurs);
                    back_right.upDateDroiteMov(angleBR, longueurBR, vitesseServomoteurs);

            }
}


static Robot::getHandle()
{
return handle;
}


void Robot::originRobot()
{
    StructPatte w_middle = Patte.getPointMiddle();

            front_left.resetStep();
            front_right.resetStep();
            middle_left.resetStep();
            middle_right.resetStep();
            back_left.resetStep();
            back_right.resetStep();


                front_left.setPosAll(w_middle.getAngleCoxa(), w_middle.getAngleFemur(), w_middle.getAngleTibia(), (char)256);
                front_right.setPosAll(w_middle.getAngleCoxa(), w_middle.getAngleFemur(), w_middle.getAngleTibia(), (char)256);
                middle_left.setPosAll(w_middle.getAngleCoxa(), w_middle.getAngleFemur(), w_middle.getAngleTibia(), (char)256);
                middle_right.setPosAll(w_middle.getAngleCoxa(), w_middle.getAngleFemur(), w_middle.getAngleTibia(), (char)256);
                back_left.setPosAll(w_middle.getAngleCoxa(), w_middle.getAngleFemur(), w_middle.getAngleTibia(), (char)256);
                back_right.setPosAll(w_middle.getAngleCoxa(), w_middle.getAngleFemur(), w_middle.getAngleTibia(), (char)256);

}


void Robot::MouvementX(int x_ws)
{
    if( (x_ws > (-DEAD_ZONE_JOY)) && (x_ws < (DEAD_ZONE_JOY)) )
                x_ws = 0;

            if(x_joy != x_ws)
            {
                x_joy = x_ws;
                processDirectionRobot();
            }
}


void Robot::MouvementY(int y_ws)
{
    if( (y_ws > (-DEAD_ZONE_JOY)) && (y_ws < (DEAD_ZONE_JOY)) )
                y_ws = 0;

            if(y_joy != y_ws)
            {
                y_joy = y_ws;
                processDirectionRobot();
            }
}


void Robot::MouvementZ(int z_ws)
{
    if( (z_ws > (-DEAD_ZONE_JOY)) && (z_ws < (DEAD_ZONE_JOY)) )
                z_ws = 0;

            if(z_joy != z_ws)
            {
                z_joy = z_ws;
                processDirectionRobot();
            }
}


static float Robot::getMax(float val1, float val2, float val3, float val4, float val5, float val6)
{
    float valeurMax;

            if(val1 > val2)
                valeurMax = val1;
            else
                valeurMax = val2;

            if(valeurMax < val3)
                valeurMax = val3;

            if(valeurMax < val4)
                valeurMax = val4;

            if(valeurMax < val5)
                valeurMax = val5;

            if(valeurMax < val6)
                valeurMax = val6;

            return valeurMax;
}


static int Robot::getLongueurMovCIR(float dist, float distMax)
{
    return (int)((LONGUEUR_MAX * dist) / distMax);
}


static int Robot::getAngleCIR(float distCIR, float distHypPatte, float distPatte)
{
    return (int)round(acos( ((distHypPatte * distHypPatte) + (distCIR * distCIR) - (distPatte * distPatte)) / (2 * distHypPatte * distCIR) ));
}

static float Robot::module(float x, float y)
{
    return (float)(sqrt(x*x + y*y) );
}

static int Robot::module(int x, int y)
{
    return (int)(round( sqrt(x*x + y*y) ));
}

static int Robot::arcTanDeg(int x, int y)
{
    return (int)((round(180 *(Math.atan2(y, x))/ M_Pi) + 360) % 360);
}
