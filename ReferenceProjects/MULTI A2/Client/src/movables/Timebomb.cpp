#include "hge.h"
#include "hgeSprite.h"
#include "hgefont.h"
#include "movables/Timebomb.h"
#include <string>

/**
* Asteroid Constructor
*
* It will load the file specified into a sprite and intialise its
* hotspot to the center. Assumes a sprite size of 30*30 and a
* screen size of 800*600
*
* @param filename Name of the graphics file used to represent the Asteroid
*/

Timebomb::Timebomb(float startx, float starty, int shipID)
{
    HGE* hge = hgeCreate( HGE_VERSION );
    tex_ = hge->Texture_Load( "timebomb.png" );
    hge->Release();
    sprite_.reset( new hgeSprite( tex_, 0, 0, 16, 16 ) );
    sprite_->SetHotSpot( 8, 8 );

    pos_curr_.SetX( startx );
    pos_curr_.SetY( starty );
    pos_server_.SetX( startx );
    pos_server_.SetY( starty );
    pos_client_.SetX( startx );
    pos_client_.SetY( starty );
    SetRatio( 1.0f );
	isDone = false;

    SetObjectType( MOVABLE_OBJECT_TYPE_TIMEBOMB );
	SetOwnerID(shipID);
	timer = 3;
	font_.reset(new hgeFont("font1.fnt"));
	font_->SetScale(0.5);
}

/**
* Asteroid Destructor
*
* Frees the internal texture used by the sprite
*/
Timebomb::~Timebomb()
{
    HGE* hge = hgeCreate( HGE_VERSION );
    hge->Texture_Free( tex_ );
	font_.release();
    hge->Release();
}

/**
* Render Cycle
*
* Renders the Asteroid to the screen. Must be called between a
* Gfx_BeginScene an Gfx_EndScene, otherwise bad things will
* happen.
*/
void Timebomb::Render()
{
    sprite_->RenderEx( pos_curr_.GetX(), pos_curr_.GetY(), 0);
	font_->printf(pos_curr_.GetX() - sprite_->GetWidth() * 0.5f - 5, pos_curr_.GetY() - sprite_->GetHeight() * 0.5f, HGETEXT_CENTER, std::to_string((GetTimer() + 1)).c_str());
}

//bool Asteroid::Update( float timedelta )
//{
//    float pi = 3.141592654f * 2;
//
//    pos_curr_.SetX( pos_curr_.GetX() + (velocity_.GetX() * timedelta) );
//    pos_curr_.SetY( pos_curr_.GetY() + (velocity_.GetY() * timedelta) );
//    WrapOverPos( pos_curr_ );
//
//    // Update the future position
//    pos_next_.SetX( pos_curr_.GetX() + (velocity_.GetX() * timedelta) );
//    pos_next_.SetY( pos_curr_.GetY() + (velocity_.GetY() * timedelta) );
//    WrapOverPos( pos_next_ );
//}
