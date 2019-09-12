#include "hge.h"
#include "hgesprite.h"
#include "hgeFont.h"
#include "movables/movables.h"

Movables::Movables()
{
    HGE *hge = hgeCreate( HGE_VERSION );
    screen_width_ = static_cast<float>( hge->System_GetState( HGE_SCREENWIDTH ) );
    screen_height_ = static_cast<float>( hge->System_GetState( HGE_SCREENHEIGHT ) );

    SetRatio( 1.0f );
}

Movables::~Movables()
{
}

/**
* Update cycle
*
* Increments the angular and x,y position of the ship based on how
* much time that has passed since the last frame. It also wraps the
* ship around the screen so it never goes out of screen.
*
* @param timedelta The time that has passed since the last frame in milliseconds
*/
// Part 2. Step 2. Update the variables with the server/network values
bool Movables::Update( float timedelta )
{
    // Calculate the movement.
    float pi = 3.141592654f * 2;

    float prev_x = pos_curr_.GetX();
    float prev_y = pos_curr_.GetY();

    float sprite_width = sprite_->GetWidth();
    float sprite_height = sprite_->GetHeight();

    pos_server_.SetAngular( pos_server_.GetAngular() + ( velocity_.GetAngular() * timedelta ) );
    if( pos_server_.GetAngular() > pi   ) pos_server_.SetAngular( pos_server_.GetAngular() - pi );
    if( pos_server_.GetAngular() < 0.0f ) pos_server_.SetAngular( pos_server_.GetAngular() + pi );

    pos_client_.SetAngular( pos_client_.GetAngular() + ( velocity_.GetAngular() * timedelta ) );
    if( pos_client_.GetAngular() > pi   ) pos_client_.SetAngular( pos_client_.GetAngular() - pi );
    if( pos_client_.GetAngular() < 0.0f ) pos_client_.SetAngular( pos_client_.GetAngular() + pi );

    pos_curr_.SetAngular( ( GetRatio() * pos_server_.GetAngular() ) + ( ( 1 - GetRatio() ) * pos_curr_.GetAngular() ) );
    if( pos_curr_.GetAngular() > pi   ) pos_curr_.SetAngular( pos_curr_.GetAngular() - pi );
    if( pos_curr_.GetAngular() < 0.0f ) pos_curr_.SetAngular( pos_curr_.GetAngular() + pi );

    pos_server_.SetX( pos_server_.GetX() + ( velocity_server_.GetX() * timedelta ) );
    pos_server_.SetY( pos_server_.GetY() + ( velocity_server_.GetY() * timedelta ) );
    WrapOverPos( pos_server_ );

    pos_client_.SetX( pos_client_.GetX() + ( velocity_.GetX() * timedelta ) );
    pos_client_.SetY( pos_client_.GetY() + ( velocity_.GetY() * timedelta ) );
    WrapOverPos( pos_client_ );

    // change the way movement is updated by using ratio.
    if( ( ( pos_server_.GetX() < ( -sprite_width / 2 ) ) && ( pos_client_.GetX() > ( screen_width_ + ( sprite_width / 2 ) ) ) ) ||
        ( ( pos_server_.GetX() > ( screen_width_ + ( sprite_width / 2 ) ) ) && ( pos_client_.GetX() < ( -sprite_width / 2 ) ) ) )
    {
        pos_curr_.SetX( pos_server_.GetX() );
    }
    else
    {
        pos_curr_.SetX( ( GetRatio() * pos_server_.GetX() ) + ( ( 1 - GetRatio() ) * pos_client_.GetX() ) );
    }

    if( ( ( pos_server_.GetY() < ( -sprite_height / 2 ) ) && ( pos_client_.GetY() > ( screen_height_ + ( sprite_height / 2 ) ) ) ) ||
        ( ( pos_server_.GetY() > ( screen_height_ + ( sprite_height / 2 ) ) ) && ( pos_client_.GetY() < ( -sprite_height / 2 ) ) ) )
    {
        pos_curr_.SetY( pos_server_.GetY() );
    }
    else
    {
        pos_curr_.SetY( ( GetRatio() * pos_server_.GetY() ) + ( ( 1 - GetRatio() ) * pos_client_.GetY() ) );
    }

    if( GetRatio() < 1 )
    {
        // interpolating ratio step.
        SetRatio( GetRatio() + ( timedelta * 4 ) );
        if( GetRatio() > 1 ) SetRatio( 1 );
    }
    WrapOverPos( pos_curr_ );

    // Update the future position
    pos_next_.SetX( pos_curr_.GetX() + (velocity_.GetX() * timedelta) );
    pos_next_.SetY( pos_curr_.GetY() + (velocity_.GetY() * timedelta) );
    WrapOverPos( pos_next_ );

    if( ( pos_curr_.GetX() != prev_x ) || ( pos_curr_.GetY() != prev_y ) )
    {
        return true; // something updated.
    }
    else 
		return false; // nothing updated.
}

void Movables::WrapOverPos( Position &pos )
{
    if( pos.GetX() < ( -sprite_->GetWidth() / 2 ) )
    {
        pos.SetX( pos.GetX() + ( screen_width_ + sprite_->GetWidth() ) );
    }
    else if( pos.GetX() > ( screen_width_ + ( sprite_->GetWidth() / 2 ) ) )
    {
        pos.SetX( pos.GetX() - ( screen_width_ + sprite_->GetWidth() ) );
    }

    if( pos.GetY() < ( -sprite_->GetHeight() / 2 ) )
    {
        pos.SetY( pos.GetY() + ( screen_height_ + sprite_->GetHeight() ) );
    }
    else if( pos.GetY() > ( screen_height_ + ( sprite_->GetHeight() / 2 ) ) )
    {
        pos.SetY( pos.GetY() - ( screen_height_ + sprite_->GetHeight() ) );
    }
}

void Movables::StopMoving( void )
{
    pos_curr_.Reset();
    pos_server_.Reset();
    pos_client_.Reset();
    velocity_.Reset();
    velocity_server_.Reset();
}
