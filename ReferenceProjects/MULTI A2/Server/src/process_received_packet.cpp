#include "ServerNetwork.h"
#include "process_received_packet.h"
#include "packets/packets_c2s.h"
#include "packets/packets_s2c.h"
#include "process_send_packet.h"
#include "ship.h"
#include "asteroid.h"
#include "timebomb.h"
#include "medKit.h"
#include <vector>

#ifdef _DEBUG
extern void log( const char *szFormat, ... );
#endif

extern HNet::_ServerNetwork NetObj;
extern Ship g_ShipList[];
extern std::vector <_Asteroid *> g_AsteroidList; // Asteroid list.
extern std::vector <_Timebomb *> g_TimeBombList;
extern _Medkit* currentMedkit;

void ProcessReceivedPacket( struct HNet::_ProcessSession *ToProcessSession )
{
    int PacketID;

    ToProcessSession->PacketMessage >> PacketID;
    switch( PacketID )
    {
        case PACKET_ID_C2S_ENTERGAME:
        {
            ProcessReceivedPacket_EnterGame( ToProcessSession );
        }
        break;

        case PACKET_ID_C2S_MOVEMENT:
        {
            ProcessReceivedPacket_Movement( ToProcessSession );
        }
        break;

        case PACKET_ID_C2S_COLLIDED:
        {
            ProcessReceivedPacket_Collided( ToProcessSession );
        }
        break;

        // Lab 12. Part 3. Step 3.1 Add the packet receiving codes in the server.
        case PACKET_ID_C2S_NEWMISSILE:
        {
            ProcessReceivedPacket_NewMissile( ToProcessSession );
        }
        break;

        // Lab 12. Part 4. Step 4.2 Broadcast the collided packet
        case PACKET_ID_C2S_MISSILECOLLIDED:
        {
            ProcessReceivedPacket_MissileCollided( ToProcessSession );
        }
        break;

		case PACKET_ID_C2S_NEWTIMEBOMB:
		{
			ProcessReceivedPacket_NewTimebomb(ToProcessSession);
		}
		break;

		case PACKET_ID_C2S_MEDKIT_TAKEN:
		{
			ProcessReceivedPacket_MedkitTaken(ToProcessSession);
		}
		break;
    }
}

void ProcessReceivedPacket_EnterGame( struct HNet::_ProcessSession *ToProcessSession )
{
    int ShipID = ToProcessSession->SessionIndex;
	if (ShipID > MAX_CONNECTION - 3)
	{
		struct PKT_C2S_EnterGame Data;

		ToProcessSession->PacketMessage >> Data;
		g_ShipList[ShipID].ship_type = Data.ShipType;
		g_ShipList[ShipID].x = Data.x;
		g_ShipList[ShipID].y = Data.y;
		g_ShipList[ShipID].angular = Data.angular;
		g_ShipList[ShipID].velocity_x = Data.velocity_x;
		g_ShipList[ShipID].velocity_y = Data.velocity_y;
		// at the start, this should be set to be the same?
		g_ShipList[ShipID].velocity_server_x = Data.velocity_x;
		g_ShipList[ShipID].velocity_server_y = Data.velocity_y;
		g_ShipList[ShipID].velocity_angular = Data.velocity_angular;
		g_ShipList[ShipID].hp = Data.hp;
		g_ShipList[ShipID].deathTimer = Data.deathTimer;

#ifdef _DEBUG
		log("Recv [PACKET_ID_C2S_ENTERGAME] Conn:%d, ID:%d, Type:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, av:%0.2f",
			g_ShipList[ShipID].connected, ShipID, g_ShipList[ShipID].ship_type, g_ShipList[ShipID].x, g_ShipList[ShipID].y, g_ShipList[ShipID].angular,
			g_ShipList[ShipID].velocity_x, g_ShipList[ShipID].velocity_y, g_ShipList[ShipID].velocity_angular);
#endif

		struct HNet::_PacketMessage EnterGameAckPacket;
		int EnterGameAckPacketID = PACKET_ID_S2C_ENTERGAMEOK;
		EnterGameAckPacket << EnterGameAckPacketID;
		NetObj.SendPacket(ShipID, EnterGameAckPacket);

		struct HNet::_PacketMessage NewMedkitPacket;
		struct PKT_S2C_NewMedkit NewMedkitData;
		int NewMedkitPacketID = PACKET_ID_S2C_NEWMEDKIT;
		NewMedkitData.x = currentMedkit->GetX();
		NewMedkitData.y = currentMedkit->GetY();
		NewMedkitPacket << NewMedkitPacketID;
		NewMedkitPacket << NewMedkitData;
		NetObj.SendPacket(ShipID, NewMedkitPacket);

		struct HNet::_PacketMessage NewAsteroidPacket;
		struct PKT_S2C_NewAsteroid NewAsteroidData;
		int NewAsteroidPacketID = PACKET_ID_S2C_NEWASTEROID;
		for (auto asteroid : g_AsteroidList)
		{
			NewAsteroidData.AsteroidID = asteroid->GetID();
			NewAsteroidData.x = asteroid->GetX();
			NewAsteroidData.y = asteroid->GetY();
			NewAsteroidData.velocity_x = asteroid->GetVelocityX();
			NewAsteroidData.velocity_y = asteroid->GetVelocityY();
			NewAsteroidData.velocity_angular = asteroid->GetVelocityAngular();

			NewAsteroidPacket.Reset();
			NewAsteroidPacket << NewAsteroidPacketID;
			NewAsteroidPacket << NewAsteroidData;
			NetObj.SendPacket(ShipID, NewAsteroidPacket);
		}

		// Send Info & Notice Message.
		int Index;

		struct HNet::_PacketMessage EnemyPacket;
		struct PKT_S2C_EnemyShip EnemyPacketData;
		int EnemyPacketID = PACKET_ID_S2C_ENEMYSHIP;

		struct HNet::_PacketMessage NewEnemyShipPacket;
		struct PKT_S2C_NewEnemyShip NewEnemyShipPacketData;
		int NewEnemyPacketID = PACKET_ID_S2C_NEWENEMYSHIP;
		NewEnemyShipPacketData.ShipID = ShipID;
		NewEnemyShipPacketData.ShipType = g_ShipList[ShipID].ship_type;
		NewEnemyShipPacketData.x = g_ShipList[ShipID].x;
		NewEnemyShipPacketData.y = g_ShipList[ShipID].y;
		NewEnemyShipPacketData.angular = g_ShipList[ShipID].angular;
		NewEnemyShipPacketData.velocity_x = g_ShipList[ShipID].velocity_x;
		NewEnemyShipPacketData.velocity_y = g_ShipList[ShipID].velocity_y;
		NewEnemyShipPacketData.velocity_angular = g_ShipList[ShipID].velocity_angular;
		NewEnemyShipPacketData.hp = g_ShipList[ShipID].hp;
		NewEnemyShipPacketData.deathTimer = g_ShipList[ShipID].deathTimer;

		NewEnemyShipPacket << NewEnemyPacketID;
		NewEnemyShipPacket << NewEnemyShipPacketData;

		for (Index = 1; Index <= MAX_CONNECTION; ++Index)
		{
			if (true == g_ShipList[Index].connected)
			{
				if (ShipID == Index) continue;

				// Send Info Message to SessionID.
				EnemyPacketData.ShipID = Index;
				EnemyPacketData.ShipType = g_ShipList[Index].ship_type;
				EnemyPacketData.x = g_ShipList[Index].x;
				EnemyPacketData.y = g_ShipList[Index].y;
				EnemyPacketData.angular = g_ShipList[Index].angular;
				EnemyPacketData.velocity_x = g_ShipList[Index].velocity_x;
				EnemyPacketData.velocity_y = g_ShipList[Index].velocity_y;
				EnemyPacketData.velocity_angular = g_ShipList[Index].velocity_angular;
				EnemyPacketData.hp = g_ShipList[Index].hp;
				EnemyPacketData.deathTimer = g_ShipList[Index].deathTimer;

				EnemyPacket.Reset();
				EnemyPacket << EnemyPacketID;
				EnemyPacket << EnemyPacketData;
				NetObj.SendPacket(ShipID, EnemyPacket);
#ifdef _DEBUG
				log("Send [PACKET_ID_S2C_ENEMYSHIP] to ID:%d > ShipID:%d, Type:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, av:%0.2f",
					ShipID, EnemyPacketData.ShipID, EnemyPacketData.ShipType, EnemyPacketData.x, EnemyPacketData.y, EnemyPacketData.angular,
					EnemyPacketData.velocity_x, EnemyPacketData.velocity_y, EnemyPacketData.velocity_angular);
#endif

				// Send Notice Message to Index.
				NetObj.SendPacket(Index, NewEnemyShipPacket);
#ifdef _DEBUG
				log("Send [PACKET_ID_S2C_NEWENEMYSHIP] to ID:%d > ShipID:%d, Type:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, av:%0.2f",
					Index, NewEnemyShipPacketData.ShipID, NewEnemyShipPacketData.ShipType, NewEnemyShipPacketData.x, NewEnemyShipPacketData.y, NewEnemyShipPacketData.angular,
					NewEnemyShipPacketData.velocity_x, NewEnemyShipPacketData.velocity_y, NewEnemyShipPacketData.velocity_angular);
#endif
			}
		}
	}
	else
	{
		struct HNet::_PacketMessage Packet;
		int PacketID = PACKET_ID_S2C_SERVERFULL;
		Packet << PacketID;
		NetObj.SendPacket(ShipID, Packet);
	}
}

void ProcessReceivedPacket_Movement( struct HNet::_ProcessSession *ToProcessSession )
{
    int ShipID = ToProcessSession->SessionIndex;
    struct PKT_C2S_Movement RecvData;

    // Update server data.
    ToProcessSession->PacketMessage >> RecvData;
#ifdef _DEBUG
    log("Recv [PACKET_ID_C2S_MOVEMENT] ID:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, svx:%0.2f, svy:%0.2f, sva:%0.2f",
        ShipID, RecvData.x, RecvData.y, RecvData.angular, RecvData.velocity_x, RecvData.velocity_y,
        RecvData.velocity_server_x, RecvData.velocity_server_y, RecvData.velocity_angular);
#endif
    g_ShipList[ShipID].x = RecvData.x;
    g_ShipList[ShipID].y = RecvData.y;
    g_ShipList[ShipID].angular = RecvData.angular;
    g_ShipList[ShipID].velocity_x = RecvData.velocity_x;
    g_ShipList[ShipID].velocity_y = RecvData.velocity_y;
    g_ShipList[ShipID].velocity_server_x = RecvData.velocity_server_x;
    g_ShipList[ShipID].velocity_server_y = RecvData.velocity_server_y;
    g_ShipList[ShipID].velocity_angular = RecvData.velocity_angular;
	g_ShipList[ShipID].hp = RecvData.hp;
	g_ShipList[ShipID].deathTimer = RecvData.deathTimer;

    SendPacketProcess_SpaceshipMovement( ShipID );
}

void ProcessReceivedPacket_Collided( struct HNet::_ProcessSession *ToProcessSession )
{
    struct PKT_C2S_Collided RecvData;

    // Update server data.
    ToProcessSession->PacketMessage >> RecvData;
	int ShipID = RecvData.ShipID;

    g_ShipList[ShipID].x = RecvData.x;
    g_ShipList[ShipID].y = RecvData.y;
    g_ShipList[ShipID].angular = RecvData.angular;
    g_ShipList[ShipID].velocity_x = RecvData.velocity_x;
    g_ShipList[ShipID].velocity_y = RecvData.velocity_y;
    g_ShipList[ShipID].velocity_server_x = RecvData.velocity_server_x;
    g_ShipList[ShipID].velocity_server_y = RecvData.velocity_server_y;
    g_ShipList[ShipID].velocity_angular = RecvData.velocity_angular;
	g_ShipList[ShipID].hp = RecvData.hp;
	g_ShipList[ShipID].deathTimer = RecvData.deathTimer;

    // Send to everyone
    struct HNet::_PacketMessage SendPacket;
    struct PKT_S2C_Collided SendData;
    int PacketID = PACKET_ID_S2C_COLLIDED;

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
}

// Lab 12. Part 3. Step 3.2 Add the packet receiving codes in the server.
void ProcessReceivedPacket_NewMissile( struct HNet::_ProcessSession *ToProcessSession )
{
    struct PKT_C2S_NewMissile RecvData;
    ToProcessSession->PacketMessage >> RecvData;

    // Send to everyone
    struct HNet::_PacketMessage SendPacket;
    struct PKT_S2C_NewMissile SendData;
    int PacketID = PACKET_ID_S2C_NEWMISSILE;

    SendData.OwnerShipID = RecvData.OwnerShipID;
    SendData.x = RecvData.x;
    SendData.y = RecvData.y;
    SendData.angular = RecvData.angular;
    SendData.velocity_server_x = RecvData.velocity_x;
    SendData.velocity_server_y = RecvData.velocity_y;
    SendData.velocity_angular = RecvData.velocity_angular;

    SendPacket << PacketID;
    SendPacket << SendData;
    NetObj.SendPacketToAll( SendPacket );
#ifdef _DEBUG
    log( "Send: PACKET_ID_S2C_NEWMISSILE, OwnerShipID:%d, x:%0.2f, y:%0.2f, a:%0.2f, vsx:%0.2f, vsy:%0.2f, va:%0.2f",
         SendData.OwnerShipID, SendData.x, SendData.y, SendData.angular, SendData.velocity_server_x, SendData.velocity_server_y, SendData.velocity_angular );
#endif
}

// Lab 12. Part 4. Step 4.2 Broadcast the collided packet
void ProcessReceivedPacket_MissileCollided( struct HNet::_ProcessSession *ToProcessSession )
{
    struct PKT_C2S_MissileCollided RecvData;
    ToProcessSession->PacketMessage >> RecvData;

    // Send to everyone
    struct HNet::_PacketMessage SendPacket;
    struct PKT_S2C_MissileCollided SendData;
    int PacketID = PACKET_ID_S2C_MISSILECOLLIDED;

    SendData.missile.OwnerShipID = RecvData.missile.OwnerShipID;
    SendData.collided_object.type = RecvData.collided_object.type;
    SendData.collided_object.id = RecvData.collided_object.id;

    SendPacket << PacketID;
    SendPacket << SendData;
    NetObj.SendPacketToAll( SendPacket );
#ifdef _DEBUG
    log( "Send: PACKET_ID_S2C_MISSILECOLLIDED, OwnerShipID:%d, CollidedObjectType:%d, CollidedObjectID:%d",
         SendData.missile.OwnerShipID, SendData.collided_object.type, SendData.collided_object.id );
#endif
}

void ProcessReceivedPacket_NewTimebomb(struct HNet::_ProcessSession *ToProcessSession)
{
	struct PKT_C2S_NewTimebomb RecvData;
	ToProcessSession->PacketMessage >> RecvData;

	// Send to everyone
	struct HNet::_PacketMessage SendPacket;
	struct PKT_C2S_NewTimebomb SendData;
	int PacketID = PACKET_ID_S2C_NEWTIMEBOMB;

	SendData.OwnerShipID = RecvData.OwnerShipID;
	SendData.x = RecvData.x;
	SendData.y = RecvData.y;

	_Timebomb* newbomb = new _Timebomb(SendData.OwnerShipID, SendData.x, SendData.y);
	g_TimeBombList.push_back(newbomb);

	SendPacket << PacketID;
	SendPacket << SendData;
	NetObj.SendPacketToAll(SendPacket);
#ifdef _DEBUG
	log("Send: PACKET_ID_S2C_NEWTIMEBOMB, OwnerShipID:%d, x:%0.2f, y:%0.2f",
		SendData.OwnerShipID, SendData.x, SendData.y);
#endif
}

void ProcessReceivedPacket_MedkitTaken(struct HNet::_ProcessSession *ToProcessSession)
{
	struct PKT_C2S_MedkitTaken RecvData;
	ToProcessSession->PacketMessage >> RecvData;

	// Send to everyone
	struct HNet::_PacketMessage SendPacket;
	struct PKT_C2S_MedkitTaken SendData;
	int PacketID = PACKET_ID_S2C_MEDKIT_TAKEN;

	SendData.TakenShipID = RecvData.TakenShipID;
	SendData.x = RecvData.x;
	SendData.y = RecvData.y;

	delete currentMedkit;
	currentMedkit = NULL;

	SendPacket << PacketID;
	SendPacket << SendData;
	NetObj.SendPacketToAll(SendPacket);
#ifdef _DEBUG
	log("Send: PACKET_ID_S2C_MEDKIT_TAKEN, TakenShipID:%d, x:%0.2f, y:%0.2f",
		SendData.TakenShipID, SendData.x, SendData.y);
#endif
}