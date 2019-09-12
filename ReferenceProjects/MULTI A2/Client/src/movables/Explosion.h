#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "movables.h"

class Explosion : public Movables
{
    public:
        int id_;
		float existtime_;

    public: // Constructors and Destructor.
		Explosion( float startx, float starty);
    	~Explosion();

    public: // Getters and Setters.
        void SetID( int id ) { id_ = id;   }
    	int  GetID( void )   { return id_; }

    public: // Interface functions.
		bool UpdateTime(float timedelta);
    	void Render( void );
};

#endif
