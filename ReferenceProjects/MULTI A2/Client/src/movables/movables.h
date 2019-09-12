#ifndef _MOVABLES_H_
#define _MOVABLES_H_


#include <memory>
#include "hge.h"
#include "hgesprite.h"
#include "hgeFont.h"

/**
* The Movables class represents a super class for any of movable object
* which is floating in space. It obeys 2D physics in therms of displacement,
* velocity and acceleration, as well as angular position and displacement.
*/

enum MOVABLE_OBJECT_TYPE
{
    MOVABLE_OBJECT_TYPE_EMPTY = 0,

    MOVABLE_OBJECT_TYPE_SPACESHIP,
    MOVABLE_OBJECT_TYPE_ENEMYSHIP,
    MOVABLE_OBJECT_TYPE_ASTEROID,
    // Lab 12. Part 2. Step 2. Add new type definition.
    MOVABLE_OBJECT_TYPE_MISSILE,
	MOVABLE_OBJECT_TYPE_BOOM,
	MOVABLE_OBJECT_TYPE_TIMEBOMB,
	MOVABLE_OBJECT_TYPE_EXPLOSION,
	MOVABLE_OBJECT_TYPE_MEDKIT,
    MOVABLE_OBJECT_TYPE_MAX
};

class Position
{
    private:
        float x_; // The x-ordinate of the ship
        float y_; // The y-ordinate of the ship
        float angular_; // The angular position of the ship

    public:
        float GetX      ( void                ) { return x_;          }
        void  SetX      ( const float x       ) { x_ = x;             }
        float GetY      ( void                ) { return y_;          }
        void  SetY      ( const float y       ) { y_ = y;             }
        float GetAngular( void                ) { return angular_;    }
        void  SetAngular( const float angular ) { angular_ = angular; }

    public:
        Position() : x_( 0 ), y_( 0 ), angular_( 0 ) {}
        ~Position() {}

    public:
        void Reset( void ) { x_ = 0; y_ = 0; angular_ = 0; }
};

class Movables
{
    public:
        Movables();
        ~Movables();

    private:
        int object_type_;
        float screen_width_;
        float screen_height_;
        float ratio_;

    public:
        HTEXTURE tex_; // Handle to the sprite's texture
        std::unique_ptr<hgeSprite> sprite_; // The sprite used to display the asteroid

    public:
        Position pos_curr_, pos_next_, velocity_;
        Position pos_client_, pos_server_, velocity_server_;

    public:
        void  SetObjectType( const int object_type ) { this->object_type_ = object_type; }
        int   GetObjectType( void                  ) { return this->object_type_;        }

        float GetRatio( void              ) { return this->ratio_;  }
        void  SetRatio( const float ratio ) { this->ratio_ = ratio; }

    public:
        bool Update( float timedelta );
        void WrapOverPos( Position &pos );
        void StopMoving( void );
};


#endif