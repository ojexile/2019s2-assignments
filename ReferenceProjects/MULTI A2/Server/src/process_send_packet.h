#ifndef _SENDPACKET_H
#define _SENDPACKET_H

#include "asteroid.h"
#include "timebomb.h"
#include "medKit.h"

///////////////////////////////////////////////////////////////////////////////
// Global function declarations.
void SendPacket_NewAccept( const int SessionID );
void SendPacketProcess_DisconnectEnemyShip( const int SessionID );
void SendPacketProcess_SpaceshipMovement( const int SessionID );
void SendPacketProcess_AsteroidMovement( _Asteroid &asteroid );
void SendPacketProcess_AsteroidCollidedWithShip( _Asteroid &asteroid, int &ship_id );
void SendPacketProcess_TimebombTimer(_Timebomb &timebomb);
void SendPacketProcess_MedKitSpawned(_Medkit &medkit);

#endif