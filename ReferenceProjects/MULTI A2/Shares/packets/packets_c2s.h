#ifndef _PACKETS_C2S_H
#define _PACKETS_C2S_H

enum _PACKET_ID_CLIENT_TO_SERVER {
    PACKET_ID_C2S_EMPTY = 0,            // Start of the list. Do not remove this.

    PACKET_ID_C2S_ENTERGAME,
    PACKET_ID_C2S_MOVEMENT,
    PACKET_ID_C2S_COLLIDED,
    // Lab 12. Part 3. Step 1.1 Add the new packet IDs.
    PACKET_ID_C2S_NEWMISSILE,
    PACKET_ID_C2S_DELETEMISSILE,
    // Lab 12. Part 4. Step 2.1 Add the new packet ID and structure.
    PACKET_ID_C2S_MISSILECOLLIDED,
	PACKET_ID_C2S_NEWTIMEBOMB,
	PACKET_ID_C2S_MEDKIT_TAKEN,
    PACKET_ID_C2S_END                   // This is the indicator for the end of the list. Do not put any packet ID after this.
};


/**
* This is the list of data structures for each packet.
* ** IMPORTANT ** All the structures have to be fixed size.
*/
#pragma pack(push, 1) // Pack the memory alignment. 
struct PKT_C2S_EnterGame
{
    int ShipID;
    int ShipType;
    float x;
    float y;
    float angular;
    float velocity_x;
    float velocity_y;
    float velocity_angular;
	int hp;
	float deathTimer;
};

struct PKT_C2S_Movement
{
    int ShipID;
    float x;
    float y;
    float angular;
    float velocity_x;
    float velocity_y;
    float velocity_angular;
    float velocity_server_x;
    float velocity_server_y;
	int hp;
	float deathTimer;
};

struct PKT_C2S_Collided {
    int   ShipID;
    float x;
    float y;
    float angular;
    float velocity_x;
    float velocity_y;
    float velocity_angular;
    float velocity_server_x;
    float velocity_server_y;
	int hp;
	float deathTimer;
};

// Lab 12. Part 3. Step 1.2 Add the packet structures for the new packet IDs
struct PKT_C2S_NewMissile
{
    int OwnerShipID;
    float x;
    float y;
    float angular;
    float velocity_x;
    float velocity_y;
    float velocity_angular;
};

struct PKT_C2S_DeleteMissile
{
    int OwnerShipID;
};

// Lab 12. Part 4. Step 2.1 Add the new packet ID and structure.
struct PKT_C2S_MissileCollided
{
    struct
    {
        int OwnerShipID;
    } missile;

    struct
    {
        int type;
        int id;
    } collided_object;
};

struct PKT_C2S_NewTimebomb
{
	int OwnerShipID;
	float x;
	float y;
};

struct PKT_C2S_MedkitTaken
{
	int TakenShipID;
	float x;
	float y;
};

#pragma pack(pop) // Return back to default memory alignment.
#endif