#ifndef _SHIP_H_
#define _SHIP_H_

#include <string>
#include "hge.h"
#include "hgeSprite.h"
#include "hgefont.h"
#include "movables/movables.h"

class hgeSprite;
class hgeFont;

/**
* The Ship class represents a single spaceship floating in space.
* The size of the current art is 128*128 pixels
*/
class Ship : public Movables
{
    public:
        std::unique_ptr<hgeFont> font_; 
		std::unique_ptr<hgeSprite> hp_;

    private:
        std::string shipname_;
        int shipid_;
        int shiptype_;
		int hp;
		float deathTimer;

    public:
        Ship( int shiptype, std::string shipname, float startx, float starty, float startw  = 0.0f );
    	~Ship();

    public:
    	void Render();
    	void Accelerate(float acceleration, float timedelta);

    public:
        void        SetShipName( std::string shipname ) { shipname_ = shipname; }
        std::string GetShipName( void                 ) { return shipname_;     }
        void        SetShipID  ( int shipid           ) { shipid_ = shipid;     }
        int         GetShipID  ( void                 ) { return shipid_;       }
        void        SetShipType( int shiptype         ) { shiptype_ = shiptype; }
        int         GetShipType( void                 ) { return shiptype_;     }
		void        SetShipHP(int _hp) { hp = _hp; }
		int         GetShipHP(void) { return hp; }
		void        SetShipDeathTimer(float _dt) { deathTimer = _dt; }
		float       GetShipDeathTimer(void) { return deathTimer; }
		void        SetPos(float startx, float starty, float start_angular);
};

#endif