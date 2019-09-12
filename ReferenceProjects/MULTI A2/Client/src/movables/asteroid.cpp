#include "hge.h"
#include "hgeSprite.h"
#include "hgefont.h"
#include "movables/asteroid.h"


/**
* Asteroid Constructor
*
* It will load the file specified into a sprite and intialise its
* hotspot to the center. Assumes a sprite size of 30*30 and a
* screen size of 800*600
*
* @param filename Name of the graphics file used to represent the Asteroid
*/

Asteroid::Asteroid( char* filename, float startx, float starty, float start_angular )
{
    HGE* hge = hgeCreate( HGE_VERSION );
    tex_ = hge->Texture_Load( filename );
    hge->Release();
    sprite_.reset( new hgeSprite( tex_, 0, 0, 30, 30 ) );
    sprite_->SetHotSpot( 15, 15 );

    pos_curr_.SetX( startx );
    pos_curr_.SetY( starty );
    pos_curr_.SetAngular( start_angular );
    pos_server_.SetX( startx );
    pos_server_.SetY( starty );
    pos_server_.SetAngular( start_angular );
    pos_client_.SetX( startx );
    pos_client_.SetY( starty );
    pos_client_.SetAngular( start_angular );
    SetRatio( 1.0f );

    SetObjectType( MOVABLE_OBJECT_TYPE_ASTEROID );
}

/**
* Asteroid Destructor
*
* Frees the internal texture used by the sprite
*/
Asteroid::~Asteroid()
{
    HGE* hge = hgeCreate( HGE_VERSION );
    hge->Texture_Free( tex_ );
    hge->Release();
}

/**
* Render Cycle
*
* Renders the Asteroid to the screen. Must be called between a
* Gfx_BeginScene an Gfx_EndScene, otherwise bad things will
* happen.
*/
void Asteroid::Render()
{
    sprite_->RenderEx( pos_curr_.GetX(), pos_curr_.GetY(), pos_curr_.GetAngular() );
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
