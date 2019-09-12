#ifndef _SHIP_H
#define _SHIP_H


struct Ship
{
    bool connected;
    int  ship_type;

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

    // Lab 12. Part 1. Step 1.2 Add collision checking codes in the server
    int image_size;

    Ship() : connected(false), x(0), y(0), angular(0), velocity_x(0), velocity_y(0), velocity_server_x(0), velocity_server_y(0), velocity_angular(0), ship_type(0)
    {
        image_size = 64;
    }
};


#endif