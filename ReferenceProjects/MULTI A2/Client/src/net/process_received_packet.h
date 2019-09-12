#ifndef _PROCESSPACKET_H
#define _PROCESSPACKET_H
#pragma once

#include "application.h"

// Function declarerations.
namespace Net {
    void ProcessReceviedPacket( Application &thisapp );

    void ProcessReceivedPacket_WelcomeMessage( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
    void ProcessReceivedPacket_NewEnemyShip( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
    void ProcessReceivedPacket_NewAstreroid( Application &thisapp, struct HNet::_ProcessSession &ToProcessSessoin );
    void ProcessReceivedPacket_DisconnectedEnemyShip( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
    void ProcessReceivedPacket_Movement( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
    void ProcessReceviedPacket_Collided( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
    void ProcessReceivedPacket_AsteroidMovement( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
    void ProcessReceivedPacket_AsteroidCollided( Application &thisapp, struct HNet::_ProcessSession &ToProsessSession );
    void ProcessReceivedPacket_NewMissile( Application &thisapp, struct HNet::_ProcessSession &ToProsessSession );
    void ProcessReceivedPacket_MissileCollided( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession );
	void ProcessReceivedPacket_NewTimebomb(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession);
	void ProcessReceivedPacket_TimebombTimer(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession);
	void ProcessReceivedPacket_NewMedkit(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession);
	void ProcessReceivedPacket_MedkitTaken(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession);
}



#endif
