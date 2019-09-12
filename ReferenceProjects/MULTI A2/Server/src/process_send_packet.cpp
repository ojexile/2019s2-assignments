#include "ServerNetwork.h"
#include "packets/packets_s2c.h"
#include "ship.h"
#include "asteroid.h"
#include "timebomb.h"
#include "process_send_packet.h"

#ifdef _DEBUG
extern void log( const char *szFormat, ... );
#endif

extern HNet::_ServerNetwork NetObj;
extern Ship g_ShipList[];

void SendPacket_NewAccept( const int SessionID )
{
    // Add into ship ilst.
    g_ShipList[SessionID].connected = true;

    // Send Welcome packet with spaceship ID.
    struct HNet::_PacketMessage Packet;       // Create the _PacketMessage structure object.
    struct PKT_S2C_WelcomeMessage PacketData;
    int PacketID = PACKET_ID_S2C_WELCOMEMESSAGE;
    PacketData.ShipID = SessionID;
    Packet << PacketID;
    Packet << PacketData;
#ifdef _DEBUG
    log( "SENT: PACKET_ID_S2C_WELCOMEMESSAGE > SessionID:%d", SessionID );
#endif

    NetObj.SendPacket( SessionID, Packet );
}

void SendPacketProcess_DisconnectEnemyShip( const int SessionID )
{
    g_ShipList[SessionID].connected = false;

    struct HNet::_PacketMessage Packet;
    struct PKT_S2C_EnemyShipDisconnect PacketData;
    int PacketID = PACKET_ID_S2C_DISCONNECTEDENEMYSHIP;
    PacketData.ShipID = SessionID;
    Packet << PacketID;
    Packet << PacketData;

    int Index;
    for( Index = 1; Index <= MAX_CONNECTION; ++Index )
    {
        if( true == g_ShipList[Index].connected )
        {
            if( SessionID == Index ) continue;

            NetObj.SendPacket( Index, Packet );
#ifdef _DEBUG
            log( "Disconnect packet sent to SessionID:%d", Index );
#endif
        }
    }
}

void SendPacketProcess_SpaceshipMovement( const int ShipID )
{
    // Send to everyone except sender.
    struct HNet::_PacketMessage SendPacket;
    struct PKT_S2C_Movement SendData;
    int PacketID = PACKET_ID_S2C_MOVEMENT;

    SendData.ShipID = ShipID;
    SendData.x = g_ShipList[ShipID].x;
    SendData.y = g_ShipList[ShipID].y;
    SendData.angular = g_ShipList[ShipID].angular;
    SendData.velocity_x = g_ShipList[ShipID].velocity_x;
    SendData.velocity_y = g_ShipList[ShipID].velocity_y;
    SendData.velocity_server_x = g_ShipList[ShipID].velocity_server_x;
    SendData.velocity_server_y = g_ShipList[ShipID].velocity_server_y;
    SendData.velocity_angular = g_ShipList[ShipID].velocity_angular;
	SendData.hp = g_ShipList[ShipID].hp;
	SendData.deathTimer = g_ShipList[ShipID].deathTimer;
	
    SendPacket << PacketID;
    SendPacket << SendData;
    NetObj.SendPacketToAll( SendPacket );
#ifdef _DEBUG
    log( "Send [PACKET_ID_C2S_MOVEMENT] to All > ID:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, vsx:%0.2f, vsy:%0.2f, va:%0.2f",
         SendData.ShipID, SendData.x, SendData.y, SendData.angular, SendData.velocity_x, SendData.velocity_y,
         SendData.velocity_server_x, SendData.velocity_server_y, SendData.velocity_angular );
#endif
}

void SendPacketProcess_AsteroidMovement( _Asteroid &asteroid )
{
    struct HNet::_PacketMessage Packet;
    int PacketID = PACKET_ID_S2C_ASTEROIDMOVEMENT;

    struct PKT_S2C_AsteroidMovement PacketData;
    PacketData.AsteroidID = asteroid.GetID();
    PacketData.server_x = asteroid.GetX();
    PacketData.server_y = asteroid.GetY();
    PacketData.velocity_x = asteroid.GetVelocityX();
    PacketData.velocity_y = asteroid.GetVelocityY();
    PacketData.velocity_angular = asteroid.GetVelocityAngular();

    Packet << PacketID;
    Packet << PacketData;
    NetObj.SendPacketToAll( Packet );
//#ifdef _DEBUG
//    log( "Send [PACKET_ID_S2C_ASTEROIDMOVEMENT] to All > AsteroidID:%d, sx:%0.2f, xy:%0.2f, vx:%0.2f, vy:%0.2f, va:%0.2f",
//         PacketData.AsteroidID, PacketData.server_x, PacketData.server_y, PacketData.velocity_x, PacketData.velocity_y, PacketData.velocity_angular );
//#endif
}

// Lab 12. Part 1. Step 1.6 Add collision checking codes in the server
void SendPacketProcess_AsteroidCollidedWithShip( _Asteroid &asteroid, int &ship_id )
{
    struct HNet::_PacketMessage Packet;
    int PacketID = PACKET_ID_S2C_ASTEROIDCOLLIDED;

    struct PKT_S2C_AsteroidCollided PacketData;
    PacketData.asteroid.id = asteroid.GetID();
    PacketData.asteroid.x = asteroid.GetX();
    PacketData.asteroid.y = asteroid.GetY();
    PacketData.asteroid.velocity_x = asteroid.GetVelocityX();
    PacketData.asteroid.velocity_y = asteroid.GetVelocityY();

    PacketData.collided_object.type = OBJECT_TYPE_SPACESHIP;
    PacketData.collided_object.id = ship_id;
    PacketData.collided_object.x = g_ShipList[ship_id].x;
    PacketData.collided_object.y = g_ShipList[ship_id].y;
    PacketData.collided_object.angular = g_ShipList[ship_id].angular;
    PacketData.collided_object.velocity_server_x = g_ShipList[ship_id].velocity_server_x;
    PacketData.collided_object.velocity_server_y = g_ShipList[ship_id].velocity_server_y;
    PacketData.collided_object.velocity_angular = g_ShipList[ship_id].velocity_angular;

    Packet << PacketID;
    Packet << PacketData;
    NetObj.SendPacketToAll( Packet );
}

void SendPacketProcess_TimebombTimer(_Timebomb &timebomb)
{
	struct HNet::_PacketMessage Packet;
	int PacketID = PACKET_ID_S2C_TIMEBOMBTIMER;

	struct PKT_S2C_TimebombTimer PacketData;
	PacketData.OwnerShipID = timebomb.GetID();
	PacketData.x = timebomb.GetX();
	PacketData.y = timebomb.GetY();
	PacketData.timer = timebomb.GetTimer();

	Packet << PacketID;
	Packet << PacketData;
	NetObj.SendPacketToAll(Packet);
}

void SendPacketProcess_MedKitSpawned(_Medkit &medkit)
{
	struct HNet::_PacketMessage Packet;
	int PacketID = PACKET_ID_S2C_NEWMEDKIT;

	struct PKT_S2C_NewMedkit PacketData;
	PacketData.x = medkit.GetX();
	PacketData.y = medkit.GetY();

	Packet << PacketID;
	Packet << PacketData;
	NetObj.SendPacketToAll(Packet);
}