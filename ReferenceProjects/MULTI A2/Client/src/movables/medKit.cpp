#include "hge.h"
#include "hgeSprite.h"
#include "hgefont.h"
#include "movables/medKit.h"


/**
* Asteroid Constructor
*
* It will load the file specified into a sprite and intialise its
* hotspot to the center. Assumes a sprite size of 30*30 and a
* screen size of 800*600
*
* @param filename Name of the graphics file used to represent the Asteroid
*/

Medkit::Medkit(float startx, float starty)
{
    HGE* hge = hgeCreate( HGE_VERSION );
    tex_ = hge->Texture_Load( "medKit.png" );
    hge->Release();
    sprite_.reset( new hgeSprite( tex_, 0, 0, 64, 64 ) );
    sprite_->SetHotSpot( 32, 32 );

    pos_curr_.SetX( startx );
    pos_curr_.SetY( starty );
    pos_server_.SetX( startx );
    pos_server_.SetY( starty );
    pos_client_.SetX( startx );
    pos_client_.SetY( starty );
    SetRatio( 1.0f );

    SetObjectType(MOVABLE_OBJECT_TYPE_MEDKIT);
}

/**
* Asteroid Destructor
*
* Frees the internal texture used by the sprite
*/
Medkit::~Medkit()
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
void Medkit::Render()
{
    sprite_->RenderEx( pos_curr_.GetX(), pos_curr_.GetY(), 0 );
}
