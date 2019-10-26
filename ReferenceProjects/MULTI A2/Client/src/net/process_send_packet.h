#ifndef _SEND_PACKET_H
#define _SEND_PACKET_H
#pragma once

#include "ClientNetwork.h"
#include "movables/ship.h"
#include "movables/missile.h"
#include "movables/Timebomb.h"
#include "movables/medKit.h"

namespace Net
{
    bool send_packet_enter_game( Ship &myship );
    void send_packet_myship_movement( Ship &myship, bool updated = false );
    void send_packet_collided( Ship &myship, Ship &othership );
    void send_packet_new_missile( Missile &NewMissile );
    void send_packet_missilecollided( Missile &myMissile, const int collided_object_type, const int collided_object_id );
	void send_packet_new_timebomb(Timebomb &newTimebomb);
	void send_packet_medKit_taken(Medkit &currentMedkit);
}


#endif