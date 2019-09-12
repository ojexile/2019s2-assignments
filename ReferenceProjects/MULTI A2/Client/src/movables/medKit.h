#ifndef _MEDKIT_H_
#define _MEDKIT_H_
#pragma once


#include "movables.h"

/**
* The Asteroid class represents a single asteroid object floating in space.
* The size of the current art is 40*40 pixels
*/
class Medkit : public Movables
{
	private:
		int TakenShipID;

    public:
		Medkit( float startx,
                float starty); 
        ~Medkit();

		void SetID(int id) { TakenShipID = id; }
		int  GetID(void) { return TakenShipID; }
    public:
        void Render();
};


#endif
