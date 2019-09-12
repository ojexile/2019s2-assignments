#include "net/process_send_packet.h"
#include "packets/packets_c2s.h"
#include "movables/ship.h"
#include "movables/asteroid.h"
#include "globals.h"
#include "timer/timer.h"

#ifdef _DEBUG
void log( char *szFormat, ... );
#endif


namespace Net
{ // Global variables for process_send_packet.cpp
    Timer net_timer;
    float timer_net_movement_update = 0;
}

namespace Net
{
    bool send_packet_enter_game( Ship & myship )
    {
        struct PKT_C2S_EnterGame PacketData;
        PacketData.ShipID = myship.GetShipID();
        PacketData.ShipType = myship.GetShipType();
        PacketData.x = myship.pos_curr_.GetX();
        PacketData.y = myship.pos_curr_.GetY();
        PacketData.angular = myship.pos_curr_.GetAngular();
        PacketData.velocity_x = myship.velocity_.GetX();
        PacketData.velocity_y = myship.velocity_.GetY();
        PacketData.velocity_angular = myship.velocity_.GetAngular();
		PacketData.hp = myship.GetShipHP();

        struct HNet::_PacketMessage Packet;
        int PacketID = PACKET_ID_C2S_ENTERGAME;
        Packet << PacketID;
        Packet << PacketData;
        Global::NetObj.SendPacket( Packet );
#ifdef _DEBUG
        log("Send: PACKET_ID_C2S_ENTERGAME, ID:%d, Type:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, va:%0.2f ",
             PacketData.ShipID, PacketData.ShipType, PacketData.x, PacketData.y, PacketData.angular, PacketData.velocity_x, PacketData.velocity_y, PacketData.velocity_angular );
#endif

        return true;
    }

    void send_packet_myship_movement( Ship &myship, bool updated )
    {
        timer_net_movement_update += net_timer.GetTimer_msec();
        if( (true == updated) || (timer_net_movement_update > 200.0f) )
        {
            timer_net_movement_update = 0;

            struct PKT_C2S_Movement PacketData;
            PacketData.ShipID = myship.GetShipID();
            PacketData.x = myship.pos_curr_.GetX();
            PacketData.y = myship.pos_curr_.GetY();
            PacketData.angular = myship.pos_curr_.GetAngular();
            PacketData.velocity_x = myship.velocity_.GetX();
            PacketData.velocity_y = myship.velocity_.GetY();
            PacketData.velocity_angular = myship.velocity_.GetAngular();
            PacketData.velocity_server_x = myship.velocity_server_.GetX();
            PacketData.velocity_server_y = myship.velocity_server_.GetY();
			PacketData.hp = myship.GetShipHP();

            struct HNet::_PacketMessage Packet;
            int PacketID = PACKET_ID_C2S_MOVEMENT;
            Packet << PacketID;
            Packet << PacketData;
            Global::NetObj.SendPacket( Packet );
#ifdef _DEBUG
        log("Send: PACKET_ID_C2S_MOVEMENT, ID:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, vsx:%0.2f, vsy:%0.2f, va:%0.2f ",
             PacketData.ShipID, PacketData.x, PacketData.y, PacketData.angular, PacketData.velocity_x, PacketData.velocity_y,
             PacketData.velocity_server_x, PacketData.velocity_server_x, PacketData.velocity_angular );
#endif
        }
    }

    void send_packet_collided( Ship &myship, Ship &othership)
    {
        struct PKT_C2S_Collided PacketData;
		struct PKT_C2S_Collided PacketData2;
        PacketData.ShipID = myship.GetShipID();
        PacketData.x = myship.pos_curr_.GetX();
        PacketData.y = myship.pos_curr_.GetY();
        PacketData.angular = myship.pos_curr_.GetAngular();
        PacketData.velocity_x = myship.velocity_.GetX();
        PacketData.velocity_y = myship.velocity_.GetY();
        PacketData.velocity_server_x = myship.velocity_server_.GetX();
        PacketData.velocity_server_y = myship.velocity_server_.GetY();
        PacketData.velocity_angular = myship.velocity_.GetAngular();
		PacketData.hp = myship.GetShipHP();

		PacketData2.ShipID = othership.GetShipID();
		PacketData2.x = othership.pos_curr_.GetX();
		PacketData2.y = othership.pos_curr_.GetY();
		PacketData2.angular = othership.pos_curr_.GetAngular();
		PacketData2.velocity_x = othership.velocity_.GetX();
		PacketData2.velocity_y = othership.velocity_.GetY();
		PacketData2.velocity_server_x = othership.velocity_server_.GetX();
		PacketData2.velocity_server_y = othership.velocity_server_.GetY();
		PacketData2.velocity_angular = othership.velocity_.GetAngular();
		PacketData2.hp = othership.GetShipHP();

        struct HNet::_PacketMessage Packet, Packet2;
        int PacketID = PACKET_ID_C2S_COLLIDED;
        Packet << PacketID;
        Packet << PacketData;
        Global::NetObj.SendPacket( Packet );
		Packet2 << PacketID;
		Packet2 << PacketData2;
		Global::NetObj.SendPacket( Packet2 );
#ifdef _DEBUG
        log( "Send: PACKET_ID_C2S_COLLIDED, ID:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, svx:%0.2f, svy:%0.2f, va:%0.2f",
             PacketData.ShipID, PacketData.x, PacketData.y, PacketData.angular, PacketData.velocity_x, PacketData.velocity_y,
             PacketData.velocity_server_x, PacketData.velocity_server_y, PacketData.velocity_angular );
#endif
    }

    // Lab 12. Part 3. Step 2.2 Send the new missile information to the server
    void send_packet_new_missile( Missile &NewMissile )
    {
        struct PKT_C2S_NewMissile PacketData;
        PacketData.OwnerShipID = NewMissile.GetOwnerID();
        PacketData.x = NewMissile.pos_curr_.GetX();
        PacketData.y = NewMissile.pos_curr_.GetY();
        PacketData.angular = NewMissile.pos_curr_.GetAngular();
        PacketData.velocity_x = NewMissile.velocity_server_.GetX();
        PacketData.velocity_y = NewMissile.velocity_server_.GetY();
        PacketData.velocity_angular = NewMissile.velocity_.GetAngular();

        struct HNet::_PacketMessage Packet;
        int PacketID = PACKET_ID_C2S_NEWMISSILE;
        Packet << PacketID;
        Packet << PacketData;
        Global::NetObj.SendPacket( Packet );
#ifdef _DEBUG
        log("Send: PACKET_ID_C2S_NEWMISSILE, OwnerID:%d, x:%0.2f, y:%0.2f, a:%0.2f, sx:%0.2f, sy:%0.2f, va:%0.2f",
             PacketData.OwnerShipID, PacketData.x, PacketData.y, PacketData.angular, PacketData.velocity_x, PacketData.velocity_y, PacketData.velocity_angular );
#endif
    }

    // Lab 12. Part 4. Step 2.2 Add the send_packet_missilecollided() function
    void send_packet_missilecollided( Missile &myMissile, const int collided_object_type, const int collided_object_id )
    {
        struct PKT_C2S_MissileCollided PacketData;
        PacketData.missile.OwnerShipID = myMissile.GetOwnerID();
        PacketData.collided_object.type = collided_object_type;
        PacketData.collided_object.id = collided_object_id;

        struct HNet::_PacketMessage Packet;
        int PacketID = PACKET_ID_C2S_MISSILECOLLIDED;
        Packet << PacketID;
        Packet << PacketData;
        Global::NetObj.SendPacket( Packet );
#ifdef _DEBUG
        log( "Send: PACKET_ID_C2S_MISSILECOLLIDED, MissileOwner:%d, CollidedObjectType:%d, CollidedObjectID:%d",
             PacketData.missile.OwnerShipID, PacketData.collided_object.type, PacketData.collided_object.id );
#endif
    }

	void send_packet_new_timebomb(Timebomb &newTimebomb)
	{
		struct PKT_C2S_NewTimebomb PacketData;
		PacketData.OwnerShipID = newTimebomb.GetOwnerID();
		PacketData.x = newTimebomb.pos_curr_.GetX();
		PacketData.y = newTimebomb.pos_curr_.GetY();

		struct HNet::_PacketMessage Packet;
		int PacketID = PACKET_ID_C2S_NEWTIMEBOMB;
		Packet << PacketID;
		Packet << PacketData;
		Global::NetObj.SendPacket(Packet);
#ifdef _DEBUG
		log("Send: PACKET_ID_C2S_NEWTIMEBOMB, OwnerID:%d, x:%0.2f, y:%0.2f",
			PacketData.OwnerShipID, PacketData.x, PacketData.y);
#endif
	}

	void send_packet_medKit_taken(Medkit &currentMedkit)
	{
		struct PKT_C2S_MedkitTaken PacketData;
		PacketData.TakenShipID = currentMedkit.GetID();
		PacketData.x = currentMedkit.pos_curr_.GetX();
		PacketData.y = currentMedkit.pos_curr_.GetY();

		struct HNet::_PacketMessage Packet;
		int PacketID = PACKET_ID_C2S_MEDKIT_TAKEN;
		Packet << PacketID;
		Packet << PacketData;
		Global::NetObj.SendPacket(Packet);
#ifdef _DEBUG
		log("Send: PACKET_ID_C2S_MEDKIT_TAKEN, TakenShipID:%d, x:%0.2f, y:%0.2f",
			PacketData.TakenShipID, PacketData.x, PacketData.y);
#endif
	}
}
