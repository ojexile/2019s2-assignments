#include "movables/ship.h"


/**
* Ship Constructor
*
* It will load the file specified into a sprite and intialise its
* hotspot to the center. Assumes a sprite size of 128*128 and a
* screen size of 800*600
*
* @param filename Name of the graphics file used to represent the ship
*/
Ship::Ship( int shiptype, std::string shipname, float startx, float starty, float start_angular )
{
    HGE* hge = hgeCreate( HGE_VERSION );
    std::string shipfilename = "ship" + std::to_string( shiptype ) + ".png";
    tex_ = hge->Texture_Load( shipfilename.c_str() );
	HTEXTURE hpTex = hge->Texture_Load("hp.png");

    hge->Release();

    sprite_.reset( new hgeSprite( tex_, 0, 0, 64, 64 ) );
    sprite_->SetHotSpot( 32, 32 );	
	hp_.reset(new hgeSprite(hpTex, 0, 0, 10, 10));
	hp_->SetHotSpot(5, 5);

    SetShipType( shiptype );
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

    SetObjectType( MOVABLE_OBJECT_TYPE_SPACESHIP );

    font_.reset( new hgeFont( "font1.fnt" ) );
    font_->SetScale( 0.5 );
    SetShipName( shipname );
    SetShipID( 0 );
	SetShipHP(5);
	SetShipDeathTimer(0);
}

/**
* Ship Destructor
*
* Frees the internal texture used by the sprite
*/
Ship::~Ship()
{
	HGE* hge = hgeCreate(HGE_VERSION);
	hge->Texture_Free(tex_);
	hge->Release();
}

void Ship::SetPos(float startx, float starty, float start_angular)
{
	pos_curr_.SetX(startx);
	pos_curr_.SetY(starty);
	pos_curr_.SetAngular(start_angular);
	pos_server_.SetX(startx);
	pos_server_.SetY(starty);
	pos_server_.SetAngular(start_angular);
	pos_client_.SetX(startx);
	pos_client_.SetY(starty);
	pos_client_.SetAngular(start_angular);
}

/**
* Render Cycle
*
* Renders the ship to the screen. Must be called between a
* Gfx_BeginScene an Gfx_EndScene, otherwise bad things will
* happen.
*/

void Ship::Render()
{
	sprite_->RenderEx(pos_curr_.GetX(), pos_curr_.GetY(), pos_curr_.GetAngular());
	font_->printf(pos_curr_.GetX(), pos_curr_.GetY() + 20, HGETEXT_LEFT, "%s", GetShipName().c_str());

	if (hp > 0)
	{
		for (int i = 0; i < hp; ++i)
		{
			hp_->RenderEx(pos_curr_.GetX() - sprite_->GetWidth() * 0.5f + i * 20, pos_curr_.GetY() - 40, 0);
		}
	}
}

/**
* Accelerates a ship by the given acceleration (i.e. increases
* the ships velocity in the direction it is pointing in)
*
* @param acceleration How much to accelerate by in px/s^2
* @param timedelta Time passed since last frame
*/
void Ship::Accelerate(float acceleration, float timedelta)
{
    velocity_server_.SetX( velocity_server_.GetX() + ( acceleration * cosf( pos_curr_.GetAngular() ) * timedelta ) );
    velocity_server_.SetY( velocity_server_.GetY() + ( acceleration * sinf( pos_curr_.GetAngular() ) * timedelta ) );
}