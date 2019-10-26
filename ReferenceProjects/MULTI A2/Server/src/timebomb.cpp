#include "timebomb.h"


extern int g_ClientScreenWidth;
extern int g_ClientScreenHeight;


_Timebomb::_Timebomb( int ID, float x, float y)
{
    this->ID = ID;
    this->x = x;
    this->y = y;
	this->lastnetworkupdate = 0.0f;
	this->timer = 3;
}

_Timebomb::~_Timebomb()
{
}

void _Timebomb::Update( float timedelta)
{
	timer -= timedelta;
}
