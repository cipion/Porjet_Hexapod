#ifndef AX12_H
#define AX12_H

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

#include "ServoMoteur.h"
#include "../stdrpi/SerialRPi.h"


/**
 * Classe specifique du servomoteur AX12 (heritage avec ServoMoteur)
 *
 * @author Jeremy HERGAULT, Jean-Phillipe HAYES
 * @version 3.1
 */

class AX12 : public ServoMoteur
{
public:
    AX12(SerialRPi liaison, char ID);
	~AX12();
    void setPositionExtrapol(char angle, char vitesse);


};

#endif AX12_H
