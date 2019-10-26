#include "boom.h"
#include "movables/movables.h"
#include <hge.h>
#include <hgeSprite.h>
#include <math.h>

Boom::Boom(float startx, float starty, float start_angular)
{
	HGE* hge = hgeCreate(HGE_VERSION);

    tex_ = hge->Texture_Load( "boom.png" );
    hge->Release();
	//Update the value to ( tex_, 0, 0, 40, 40 )
    sprite_.reset( new hgeSprite( tex_, 0, 0, 40, 40 ) );
    sprite_->SetHotSpot( 20, 10 );

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

    velocity_.SetX( 200.0f * cosf( pos_curr_.GetAngular() ) );
    velocity_.SetY( 200.0f * sinf( pos_curr_.GetAngular() ) );
    velocity_server_.SetX( velocity_.GetX() );
    velocity_server_.SetY( velocity_.GetY() );

	existtime_ = 1.f;

	SetObjectType(MOVABLE_OBJECT_TYPE_BOOM);
}

Boom::~Boom()
{
	HGE* hge = hgeCreate(HGE_VERSION);
	hge->Texture_Free(tex_);
	hge->Release();
}

bool Boom::UpdateTime(float timedelta)
{
	existtime_ -= timedelta;
	if (existtime_ < 0.f) return false;
	return true;
}

void Boom::Render( void )
{
	sprite_->RenderEx( pos_curr_.GetX(), pos_curr_.GetY(), pos_curr_.GetAngular() );
}
