#include "AX12.h"


AX12::~AX12()
{
}

AX12::AX12(SerialRPi liaison, char ID)  {
    super(liaison, ID); // todo super()
}

/**
     * Methode de positionnement du servomoteur a une vitesse precise
     *
     * @param angleFinal
     * 			angle du servomoteur
     *
     * @param vitesse
     * 			vitesse du servomoteur
     */
void AX12::setPositionExtrapol(char angle, char vitesse)
{
    if(!testAngle(angle))
        throw new Exception("Erreur angle servomoteur : " + angle);
    if(!testVitesse(vitesse))
        throw new Exception("Erreur vitesse servomoteur : " + vitesse);

    // constitution de la trame RS232
    char data[] = new char[11];
    data[0] = 0xFF;									// trame init
    data[1] = 0xFF;									// trame init
    data[2] = IDServo;								// ID du servo a controler
    data[3] = 0x07;									// Longueur de la trame
    data[4] = 0x03;									// Execute une action
    data[5] = 0x1E;									// Command move
    data[6] = (char)(angle & 0xFF);					// char mouvement poid faible
    data[7] = (char)((angle & 0xFF00) >> 8);		// char mouvement poid fort
    data[8] = (char)(vitesse & 0xFF);				// char vitesse poid faible
    data[9] = (char)((vitesse & 0xFF00) >> 8);		// char vitesse poid fort
    data[10] = CalcCRC(data);						// CRC

    // envoi de la trame
    serialPi.send(data, 11); // todo
}

