#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "movables.h"

class Missile : public Movables
{
    public:
        int id_;
    	int ownerid_;

    public: // Constructors and Destructor.
        Missile( float startx, float starty, float start_angular, int shipid );
    	~Missile();

    public: // Getters and Setters.
        void SetID( int id ) { id_ = id;   }
    	int  GetID( void )   { return id_; }

        void SetOwnerID( int ownerid ) { ownerid_ = ownerid; }
    	int  GetOwnerID( void )        { return ownerid_;    }

    public: // Interface functions.
    	void Render( void );
};

#endif
