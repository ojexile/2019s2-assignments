#ifndef _ASTEROID_H_
#define _ASTEROID_H_
#pragma once


#include "movables.h"

/**
* The Asteroid class represents a single asteroid object floating in space.
* The size of the current art is 40*40 pixels
*/
class Asteroid : public Movables
{
    private:
        int id_;

    public:
        Asteroid( char* filename,
                  float startx,          // Spawning position X.
                  float starty,          // Spawning position Y.
                  float start_angular ); // For spin speed velocity.
        ~Asteroid();

    public:
        void SetID( int id ) { id_ = id; }
        int  GetID( void   ) { return id_; }

    public:
        void Render();
        // Lab 12. Part 2. Step 3. Update the asteorid movement.
//        bool Update( float timedelta );
};


#endif
