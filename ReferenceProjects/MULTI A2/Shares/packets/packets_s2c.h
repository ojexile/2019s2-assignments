#ifndef _PACKETS_S2C_H
#define _PACKETS_S2C_H


// Lab 12. Part 1. Step 1.1 Add the packet to share the collision
enum _OBJECT_TYPES
{
    OBJECT_TYPE_EMPTY = 0,

    OBJECT_TYPE_SPACESHIP,
    OBJECT_TYPE_ASTEROID,

    OBJECT_TYPE_END
};

enum _PACKET_ID_SERVER_TO_CLIENT
{
    PACKET_ID_S2C_EMPTY = 0,            // Start of the list. Do not remove this.

    PACKET_ID_S2C_WELCOMEMESSAGE,
    PACKET_ID_S2C_ENTERGAMEOK,
    PACKET_ID_S2C_ENEMYSHIP,
    PACKET_ID_S2C_NEWENEMYSHIP,
    PACKET_ID_S2C_NEWASTEROID,
    PACKET_ID_S2C_DISCONNECTEDENEMYSHIP,
    PACKET_ID_S2C_MOVEMENT,
    PACKET_ID_S2C_COLLIDED,
    PACKET_ID_S2C_ASTEROIDMOVEMENT,
    // Lab 12. Part 1. Step 1.1 Add the packet to share the collision
    PACKET_ID_S2C_ASTEROIDCOLLIDED,
    // Lab 12. Part 3. Step 3.2 Add the packet receiving codes in the server.
    PACKET_ID_S2C_NEWMISSILE,
    // Lab 12. Part 4. Step 4.1 Broadcast the collided packet
    PACKET_ID_S2C_MISSILECOLLIDED,
	PACKET_ID_S2C_SERVERFULL,
	PACKET_ID_S2C_NEWTIMEBOMB,
	PACKET_ID_S2C_TIMEBOMBTIMER,
	PACKET_ID_S2C_NEWMEDKIT,
	PACKET_ID_S2C_MEDKIT_TAKEN,
    PACKET_ID_S2C_END
};


/**
* This is the list of data structures for each packet.
* ** IMPORTANT ** All the structures have to be fixed size.
*/
#pragma pack(push, 1) // Pack the memory alignment. 
struct PKT_S2C_WelcomeMessage
{
    int ShipID; // ShipID is same as SessionID in the server.
};

struct PKT_S2C_EnemyShip
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

struct PKT_S2C_NewEnemyShip
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

struct PKT_S2C_EnemyShipDisconnect
{
    int ShipID;
};

struct PKT_S2C_Movement
{
    int   ShipID;
    float x;
    float y;
    float angular;
    float velocity_x;
    float velocity_y;
    float velocity_server_x;
    float velocity_server_y;
    float velocity_angular;
	int hp;
	float deathTimer;
};

struct PKT_S2C_Collided {
    int   ShipID;
    float x;
    float y;
    float angular;
    float velocity_x;
    float velocity_y;
    float velocity_server_x;
    float velocity_server_y;
    float velocity_angular;
	int hp;
	float deathTimer;
};

struct PKT_S2C_NewAsteroid
{
    int AsteroidID;
    float x;
    float y;
    float velocity_x;
    float velocity_y;
    float velocity_angular;
};

struct PKT_S2C_AsteroidMovement
{
    int AsteroidID;
    float server_x;
    float server_y;
    float velocity_x;
    float velocity_y;
    float velocity_angular;
};

// Lab 12. Part 1. Step 1.1 Add the packet to share the collision
struct PKT_S2C_AsteroidCollided
{
    struct
    {
        int id;
        float x;
        float y;
        float velocity_x;
        float velocity_y;
    } asteroid;

    struct
    {
        int type;
        int id;
        float x;
        float y;
        float angular;
        float velocity_server_x;
        float velocity_server_y;
        float velocity_angular;
    } collided_object;
};

// Lab 12. Part 3. Step 3.2 Add the packet receiving codes in the server.
struct PKT_S2C_NewMissile
{
    int OwnerShipID;
    float x;
    float y;
    float angular;
    float velocity_server_x;
    float velocity_server_y;
    float velocity_angular;
};

// Lab 12. Part 4. Step 4.1 Broadcast the collided packet
struct PKT_S2C_MissileCollided
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

struct PKT_S2C_NewTimebomb
{
	int OwnerShipID;
	float x;
	float y;
	float timer;
};

struct PKT_S2C_TimebombTimer
{
	int OwnerShipID;
	float x;
	float y;
	float timer;
};

struct PKT_S2C_NewMedkit
{
	float x;
	float y;
};

struct PKT_S2C_MedkitTaken
{
	int TakenShipID;
	float x;
	float y;
};

#pragma pack(pop) // Return back to default memory alignment.


#endif