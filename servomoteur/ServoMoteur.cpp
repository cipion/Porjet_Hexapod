#include "ServoMoteur.h"




ServoMoteur::~ServoMoteur()
{
}





/**
     * Constructeur de l'objet ServoMoteur
     *
     * @param liaison
     * 				Reference de la liaison RS485
     *
     * @param ID
     * 			ID du servomoteur
     */
ServoMoteur::ServoMoteur(SerialRPi liaison, char ID)
{
    if((ID >= 0) && (ID <= 253))
        IDServo = ID;
    else
        throw new Exception("Erreur ID Servo");

    serialPi = liaison;
}

/**
     * Methode de controle pour savoir si l'angle du servomoteur est correct
     *
     * @param w_angle
     * 				angle du servomoteur
     *
     * @return 1 si l'angle est correct, 0 sinon
     */
bool ServoMoteur::testAngle(char w_angle) {
    return ((w_angle >= 0) && (w_angle <= 1023));
}

/**
     * Methode de controle pour savoir si la vitesse du servomoteur est correct
     *
     * @param w_vitesse
     * 				vitesse du servomoteur
     *
     * @return 1 si la vitesse est correct, 0 sinon
     */
bool ServoMoteur::testVitesse(char w_vitesse)
{
    return ((w_vitesse >= 0) && (w_vitesse <= 1023));
}

/**
     * Methode permettant de calculer le CRC d'une trame
     *
     * @param data
     * 			Trame de data a envoyer au servomoteur
     *
     * @return le CRC de la trame
     */
char ServoMoteur::CalcCRC(char data[])
{
    int len = data[3] + 2;
    byte crc = 0;
    for (int i = 2; i <= len; i++)
    {
        crc += data[i];
    }
    return (char)((0xFF - crc) & 0xFF);
}

/**
     * Methode de positionnement du servomoteur
     *
     * @param angleFinal
     * 			angle du servomoteur
     */
void ServoMoteur::setPosition(char angleFinal)
{
    if(!testAngle(angleFinal))
        throw new Exception("Erreur angle servomoteur");

    // constitution de la trame RS232
    char data[] = new char[9];
    data[0] = 0xFF;									// trame init
    data[1] = 0xFF;									// trame init
    data[2] = IDServo;								// ID du servo a controler
    data[3] = 0x05;									// Longeur de la trame
    data[4] = 0x03;									// Execute une action
    data[5] = 0x1E;									// Command move
    data[6] = (char)(angleFinal & 0xFF);			// char mouvement poid faible
    data[7] = (char)((angleFinal & 0xFF00) >> 8);	// char mouvement poid fort
    data[8] = CalcCRC(data);						// CRC

    // envoi de la trame
    serialPi.send(data, 9);
}




