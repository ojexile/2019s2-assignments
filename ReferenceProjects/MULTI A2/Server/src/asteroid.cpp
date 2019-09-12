#include "asteroid.h"


extern int g_ClientScreenWidth;
extern int g_ClientScreenHeight;


_Asteroid::_Asteroid( int ID, float x, float y, float velocity_angular )
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocity_x = 0.0f;
    this->velocity_y = 0.0f;
    this->velocity_angular = velocity_angular;
	this->lastnetworkupdate = 0.0f;

    // Lab 12. Part 1. Step 1.2 Add collision checking codes in the server
    SetImageSize( 30 );
}

_Asteroid::~_Asteroid()
{
}

void _Asteroid::Update( float timedelta, float spritewidth, float spriteheight )
{
    float pi = 3.141592654f * 2;

    SetX( GetX() + (GetVelocityX() * timedelta) );
    SetY( GetY() + (GetVelocityY() * timedelta) );

    int screenwidth = g_ClientScreenWidth;   // define as 800
    int screenheight = g_ClientScreenHeight; // define as 600

    if( GetX() < static_cast<float>(-spritewidth / 2) )
    {
        SetX( GetX() + static_cast<float>(screenwidth + spritewidth) );
    }
    else if( GetX() > static_cast<float>(screenwidth + (spritewidth / 2)) )
    {
        SetX( GetX() - static_cast<float>(screenwidth + spritewidth) );
    }

    if( GetY() < static_cast<float>(-spriteheight / 2) )
    {
        SetY( GetY() + static_cast<float>(screenheight + spriteheight) );
    }
    else if( GetY() > static_cast<float>(screenheight + (spriteheight / 2)) )
    {
        SetY( GetY() - static_cast<float>(screenheight + spriteheight) );
    }
}
