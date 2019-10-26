#ifndef _BOOM_H_
#define _BOOM_H_

#include "movables.h"

class Boom : public Movables
{
    public:
        int id_;
		float existtime_;

    public: // Constructors and Destructor.
        Boom( float startx, float starty, float start_angular);
    	~Boom();

    public: // Getters and Setters.
        void SetID( int id ) { id_ = id;   }
    	int  GetID( void )   { return id_; }

    public: // Interface functions.
		bool UpdateTime(float timedelta);
    	void Render( void );
};

#endif
