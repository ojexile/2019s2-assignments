#include "Explosion.h"
#include "movables/movables.h"
#include <hge.h>
#include <hgeSprite.h>
#include <math.h>

Explosion::Explosion(float startx, float starty)
{
	HGE* hge = hgeCreate(HGE_VERSION);

    tex_ = hge->Texture_Load( "explosion.png" );
    hge->Release();
	//Update the value to ( tex_, 0, 0, 40, 40 )
    sprite_.reset( new hgeSprite( tex_, 0, 0, 256, 256 ) );
    sprite_->SetHotSpot( 128, 128 );

    pos_curr_.SetX( startx );
    pos_curr_.SetY( starty );
    pos_server_.SetX( startx );
    pos_server_.SetY( starty );
    pos_client_.SetX( startx );
    pos_client_.SetY( starty );
    SetRatio( 1.0f );

	existtime_ = 1.f;

	SetObjectType(MOVABLE_OBJECT_TYPE_EXPLOSION);
}

Explosion::~Explosion()
{
	HGE* hge = hgeCreate(HGE_VERSION);
	hge->Texture_Free(tex_);
	hge->Release();
}

bool Explosion::UpdateTime(float timedelta)
{
	existtime_ -= timedelta;
	if (existtime_ < 0.f) return false;
	return true;
}

void Explosion::Render( void )
{
	sprite_->RenderEx( pos_curr_.GetX(), pos_curr_.GetY(), 0);
}
