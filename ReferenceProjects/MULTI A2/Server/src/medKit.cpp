#include "medKit.h"


extern int g_ClientScreenWidth;
extern int g_ClientScreenHeight;


_Medkit::_Medkit( int TakenShipID, float x, float y)
{
    this->TakenShipID = TakenShipID;
    this->x = x;
    this->y = y;
}

_Medkit::~_Medkit()
{
}
