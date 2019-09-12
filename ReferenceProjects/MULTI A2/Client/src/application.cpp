#include "ClientNetwork.h"
#include "net/process_received_packet.h"
#include "net/process_send_packet.h"
#include "application.h"
#include "hge.h"
#include "globals.h"
#include <iostream>
#include <string>
#ifdef _DEBUG
#include <io.h>

void log( char *szFormat, ... )
{
    char Buff[1024];
    char Msg[1024];
    va_list arg;

    va_start( arg, szFormat );
    _vsnprintf_s( Msg, 1024, szFormat, arg );
    va_end( arg );

    sprintf_s( Buff, 1024, "%s\n", Msg );
    _write( 1, Buff, strlen( Buff ) );
}
#endif

/**
* Constuctor
*
* Creates an instance of the graphics engine and network engine
*/

Application::Application() : hge_( hgeCreate( HGE_VERSION ) )
{
    SetGameState( GAMESTATE_NONE );

    // Lab 12. Part 2. Step 4. Add new initialization lines into Application constructor
    mymissile_ = NULL;
	myTimebomb = NULL;
	spawnedMedkit = NULL;
    keydown_space = false;
	keydown_b = false;
}

/**
* Destructor
*
* Does nothing in particular apart from calling Shutdown
*/

Application::~Application() throw( )
{
    Shutdown();
}

/**
* Initialises the graphics system
* It should also initialise the network system
*/

bool Application::Init()
{
    SetGameState( GAMESTATE_INITIALIZING );

    hge_->System_SetState( HGE_FRAMEFUNC, Application::Loop );
    hge_->System_SetState( HGE_WINDOWED, true );
    hge_->System_SetState( HGE_USESOUND, false );
    hge_->System_SetState( HGE_TITLE, "SpaceShooter" );
    hge_->System_SetState( HGE_LOGFILE, "SpaceShooter.log" );
    hge_->System_SetState( HGE_DONTSUSPEND, true );

    if( !hge_->System_Initiate() )
    {
        return false;
    }

    srand( (unsigned int)time( NULL ) );
    // Initialize and prepare the game data & systems.
    // Initialize my own spaceship.
    int shiptype = ( rand() % 4 ) + 1;
    float startx = (float)( ( rand() % 600 ) + 100 );
    float starty = (float)( ( rand() % 400 ) + 100 );
    float startangular = 0.0f;
    myship_ = new Ship( shiptype, "MyShip", startx, starty, startangular );
	networkidletime_ = 0.0f;

	font.reset(new hgeFont("font1.fnt"));
	font->SetScale(3);
	screenWidth = static_cast<float>(hge_->System_GetState(HGE_SCREENWIDTH));
	screenHeight = static_cast<float>(hge_->System_GetState(HGE_SCREENHEIGHT));

    if( false == Global::NetObj.InitNet( HNet::APPTYPE_CLIENT, HNet::PROTOCOL_TCP, "127.0.0.1", 3456 ) )
    {
#ifdef _DEBUG
        log( "%s", Global::NetObj.GetErrorMessage() );
#endif
        return false;
    }
#ifdef _DEBUG
    log( "Successfully connected to the server!" );
#endif

	ServerFull = false;
    return true;
}

/**
* Main game loop
*
* Processes user input events
* Supposed to process network events
* Renders the ships
*
* This is a static function that is called by the graphics
* engine every frame, hence the need to loop through the
* global namespace to find itself.
*/
bool Application::Loop()
{
    Global::application->Render();
    return Global::application->Update();
}

/**
* Kick starts the everything, called from main.
*/
void Application::Start()
{
    if( Init() )
    {
        hge_->System_Start();
    }
}

/**
* Update cycle
*
* Checks for keypresses:
*   - Esc - Quits the game
*   - Left - Rotates ship left
*   - Right - Rotates ship right
*   - Up - Accelerates the ship
*   - Down - Deccelerates the ship
*
* Also calls Update() on all the ships in the universe
*/
bool Application::Update()
{
    float prev_x = myship_->pos_curr_.GetX();
    float prev_y = myship_->pos_curr_.GetY();
	float prev_velocity_x = myship_->velocity_server_.GetX();
	float prev_velocity_y = myship_->velocity_server_.GetY();
    float prev_angular = myship_->velocity_.GetAngular();

    // Check key inputs and process the movements of spaceship.
    if( hge_->Input_GetKeyState( HGEK_ESCAPE ) )
        return true;

	if (!ServerFull)
	{
		Net::ProcessReceviedPacket(*this);

		float timedelta = hge_->Timer_GetDelta();
		networkidletime_ += timedelta;

		myship_->velocity_.SetAngular(0.0f);
		if (hge_->Input_GetKeyState(HGEK_LEFT))
		{
			myship_->velocity_.SetAngular(myship_->velocity_.GetAngular() - DEFAULT_ANGULAR_VELOCITY);
		}

		if (hge_->Input_GetKeyState(HGEK_RIGHT))
		{
			myship_->velocity_.SetAngular(myship_->velocity_.GetAngular() + DEFAULT_ANGULAR_VELOCITY);
		}

		if (hge_->Input_GetKeyState(HGEK_UP))
		{
			myship_->Accelerate(DEFAULT_ACCELERATION, timedelta);
		}

		if (hge_->Input_GetKeyState(HGEK_DOWN))
		{
			myship_->Accelerate(-DEFAULT_ACCELERATION, timedelta);
		}

		if (hge_->Input_GetKeyState(HGEK_0))
		{
			myship_->StopMoving();
		}

		if (myship_->GetShipHP() > 0)
		{
			// Lab 12. Part 2. Step 6. Implement Enter key to spawn a missile
			if (hge_->Input_GetKeyState(HGEK_SPACE))
			{
				if (!keydown_space)
				{
					CreateMissile(myship_->pos_curr_.GetX(), myship_->pos_curr_.GetY(), myship_->pos_curr_.GetAngular(), myship_->GetShipID());
					keydown_space = true;
				}
			}
			else
			{
				if (keydown_space) keydown_space = false;
			}

			if (hge_->Input_GetKeyState(HGEK_B))
			{
				if (!keydown_b)
				{
					CreateTimebomb(myship_->pos_curr_.GetX(), myship_->pos_curr_.GetY(), myship_->GetShipID());
					keydown_b = true;
				}
			}
			else
			{
				if (keydown_b) keydown_b = false;
			}
		}		

		if (spawnedMedkit)
		{
			//Check for collision
			if (myship_->GetShipHP() > 0)
			{
				float dist = (myship_->pos_curr_.GetX() - spawnedMedkit->pos_client_.GetX()) * (myship_->pos_curr_.GetX() - spawnedMedkit->pos_client_.GetX()) + (myship_->pos_curr_.GetY() - spawnedMedkit->pos_client_.GetY()) * (myship_->pos_curr_.GetY() - spawnedMedkit->pos_client_.GetY());

				if (dist < 64 * 64)
				{
					spawnedMedkit->SetID(myship_->GetShipID());
					Net::send_packet_medKit_taken(*spawnedMedkit);
				}
			}
		}

		if (myTimebomb)
		{
			if (myTimebomb->isDone)
			{
				delete myTimebomb;
				myTimebomb = NULL;
			}
		}
	
		// Update my spaceship.
		if (myship_->Update(timedelta))
		{
			//what if my ship isn't moving and someone else collides to me?
			if (myship_->GetShipHP() > 0)
				CheckCollided(static_cast<Movables &> (*myship_), true);
		}

		if (myship_->GetShipHP() <= 0)
		{
			myship_->SetShipDeathTimer(myship_->GetShipDeathTimer() - timedelta);
			if (myship_->GetShipDeathTimer() <= 0)
			{
				myship_->SetShipHP(5);
				float startx = (float)((rand() % 600) + 100);
				float starty = (float)((rand() % 400) + 100);
				float startangular = 0.0f;
				myship_->SetPos(startx, starty, startangular);
				myship_->velocity_.Reset();
				myship_->velocity_server_.Reset();
				Net::send_packet_myship_movement(*myship_, false);
			}
		}

		bool turned = false;
		// the problem with this is if the ship never moved, it won't send any movement updates at all
		if (prev_angular != myship_->velocity_.GetAngular()) 
			turned = true;

		//  if( (prev_x != myship_->pos_curr_.GetX()) || (prev_y != myship_->pos_curr_.GetY()) || (true == turned) || networkidletime_ >= 5.0f )
		  // it should be if there is a change of velocity or turning then send a packet. not spam a packet everytime the ship moves
		if ((prev_velocity_x != myship_->velocity_server_.GetX()) || (prev_velocity_y != myship_->velocity_server_.GetY()) || (true == turned) || networkidletime_ >= 5.0f)
		{
			if (GAMESTATE_INPLAY == GetGameState())
			{
				Net::send_packet_myship_movement(*myship_, turned);
			}

			if (networkidletime_ >= 1.0f) 
				networkidletime_ = 0.0f; //reset idle
		}

		for (auto itr : enemyships_)
		{
			if (itr->Update(timedelta))
			{
				//perhaps you should just check your own collision? Don't check other pple's
			//    CheckCollided( static_cast<Movables &> ( *itr ) );
			}
		}

		// Lab 12. Part 2. Step 7. Update the missile
		if (mymissile_)
		{
			// Lab 12. Part 4. Step 1.1 Check the collision after Update()
			if (mymissile_->Update(timedelta))
			{
				CheckCollided(static_cast<Movables &> (*mymissile_), false);
			}
		}

		// Lab 12. Part 3. Step 5.2 Update all enemy missiles
		for (auto itr_missile : enemymissiles_)
		{
			itr_missile->Update(timedelta);
		}

		for (unsigned int i = 0; i < booms_.size(); ++i)
		{
			if (!booms_.at(i)->UpdateTime(timedelta))
			{
				// this boom has timed out
				booms_.erase(booms_.begin() + i);

				break;
			}
		}

		for (unsigned int i = 0; i < explosions_.size(); ++i)
		{
			if (!explosions_.at(i)->UpdateTime(timedelta))
			{
				// this boom has timed out
				explosions_.erase(explosions_.begin() + i);

				break;
			}
		}

		for (auto itr : asteroids_)
		{
			if (itr->Update(timedelta))
			{
				// Lab 12. Part 1. Step 2.3 Remove the collision check for the asteroids in the client
	//            CheckCollided( static_cast<Movables &> ( *itr ) );
			}
		}
	}

    return false;
}

/**
* Render Cycle
*
* Clear the screen and render all the ships
*/
void Application::Render()
{
    hge_->Gfx_BeginScene();
    hge_->Gfx_Clear( 0 );

	if (!ServerFull)
	{
		// Render my space ship
		if (myship_->GetShipHP() > 0)
		{
			myship_->Render();
		}
		else
		{
			std::string text = "Respawn in " + std::to_string((int)myship_->GetShipDeathTimer());
			font->SetScale(2);
			font->printf(screenWidth * 0.5f, screenHeight * 0.5f - font->GetScale() * 0.5f, HGETEXT_CENTER, text.c_str());
		}

		for (auto itr : enemyships_)
		{
			if(itr->GetShipHP() > 0)
				itr->Render();
		}
			
		if (spawnedMedkit)
			spawnedMedkit->Render();

		// Lab 12. Part 2. Step 8. Render the missile
		if (mymissile_) mymissile_->Render();

		if (myTimebomb) myTimebomb->Render();

		// Lab 12. Part 3. Step 5.1 Render and update all enemy missiles
		for (auto itr : enemymissiles_) itr->Render();

		for (auto itr : timebombs_) itr->Render();

		// Render booms
		for (auto itr : booms_) itr->Render();

		for (auto itr : explosions_) itr->Render();

		// Render asteroids.
		for (auto itr : asteroids_) itr->Render();
	}
	else
	{		
		std::string text = "SERVER FULL";
		font->SetScale(3);
		font->printf(screenWidth * 0.5f, screenHeight * 0.5f - font->GetScale() * 0.5f, HGETEXT_CENTER, text.c_str());
	}

    hge_->Gfx_EndScene();
}

void Application::CreateTimebomb(float x, float y, int id)
{
	if (!myTimebomb)
	{
		myTimebomb = new Timebomb(x, y, id);

		Net::send_packet_new_timebomb(*myTimebomb);
	}	
}

// Lab 12. Part 2. Step 5. Add a function to handle the creation of the missile
void Application::CreateMissile( float x, float y, float w, int id )
{
    if( mymissile_ )
    { 
		CreateBoom(
			mymissile_->pos_curr_.GetX(),
			mymissile_->pos_curr_.GetY(),
			mymissile_->pos_curr_.GetAngular(),
			mymissile_->velocity_server_.GetX() * 0.5, //so the booms move at half speed
			mymissile_->velocity_server_.GetY() * 0.5
		);

		// delete existing missile
        delete mymissile_;
        mymissile_ = 0;
    }

    // add a new missile based on the following parameter coordinates
    mymissile_ = new Missile( x, y, w, id );

    // Lab 12. Part 3. Step 2.1 send the new missile information to the server
    Net::send_packet_new_missile( *mymissile_ );
}

void Application::CreateExplosion(float x, float y)
{
	Explosion* newExplosion = new Explosion(
		x,
		y
	);

	explosions_.push_back(newExplosion);
}

void Application::CreateBoom(float x, float y, float w, float vel_x, float vel_y)
{
	Boom* newboom = new Boom(
		x,
		y,
		w
	);

	newboom->velocity_.SetX(vel_x);
	newboom->velocity_.SetY(vel_y);
	newboom->velocity_server_.SetX(vel_x);
	newboom->velocity_server_.SetY(vel_y);
	booms_.push_back(newboom);
}

/**
* Shuts down the graphics and network system
*/
void Application::Shutdown()
{
    hge_->System_Shutdown();
	font.release();
    hge_->Release();
}

template <typename T1, typename T2>
bool Application::HasCollided( T1 &object, T2 &movable )
{
    hgeRect object_collidebox;
    hgeRect movable_Collidebox;

    object.sprite_->GetBoundingBox( object.pos_curr_.GetX(), object.pos_curr_.GetY(), &object_collidebox );
    movable.sprite_->GetBoundingBox( movable.pos_curr_.GetX(), movable.pos_curr_.GetY(), &movable_Collidebox );
    return object_collidebox.Intersect( &movable_Collidebox );
}

template <typename Mov, typename Tgt>
void Application::VelocityTransferByCollision( Mov &moving_obj, Tgt &other )
{
    float moving_velocity_x = moving_obj.velocity_.GetX();
    float moving_velocity_y = moving_obj.velocity_.GetY();
    float moving_velocity_server_x = moving_obj.velocity_server_.GetX();
    float moving_velocity_server_y = moving_obj.velocity_server_.GetY();
    float other_velocity_x = other.velocity_.GetX();
    float other_velocity_y = other.velocity_.GetY();
    float other_velocity_server_x = other.velocity_server_.GetX();
    float other_velocity_server_y = other.velocity_server_.GetY();

	// technically you can't assume the moving_obj is the one that is moving
    if( ( 0.0f == other_velocity_server_x ) && ( 0.0f == other_velocity_server_y ) )
    {
		log("ZERO VELOCITY other\n");
        moving_obj.velocity_.SetX( ( -moving_velocity_x ) / 2.0f );
        moving_obj.velocity_.SetY( ( -moving_velocity_y ) / 2.0f );
        moving_obj.velocity_server_.SetX( ( -moving_velocity_server_x ) / 2.0f );
        moving_obj.velocity_server_.SetY( ( -moving_velocity_server_y ) / 2.0f );
        other.velocity_.SetX( moving_velocity_x / 2.0f);
        other.velocity_.SetY( moving_velocity_y / 2.0f);
        other.velocity_server_.SetX( moving_velocity_server_x / 2.0f);
        other.velocity_server_.SetY( moving_velocity_server_y / 2.0f);
    }
	else  if ((0.0f == moving_velocity_server_x) && (0.0f == moving_velocity_server_y))
	{
		log("ZERO VELOCITY moving \n");
		moving_obj.velocity_.SetX(( other_velocity_x) / 2.0f);
		moving_obj.velocity_.SetY(( other_velocity_y) / 2.0f);
		moving_obj.velocity_server_.SetX(( other_velocity_server_x) / 2.0f);
		moving_obj.velocity_server_.SetY(( other_velocity_server_y) / 2.0f);
		other.velocity_.SetX(-other_velocity_x / 2.0f);
		other.velocity_.SetY(-other_velocity_y / 2.0f);
		other.velocity_server_.SetX(-other_velocity_server_x / 2.0f);
		other.velocity_server_.SetY(-other_velocity_server_y / 2.0f);
	}
    else
    {
        float distance_curr = 0.0f;
        float distance_next = 0.0f;

        distance_curr = ( ( ( moving_obj.pos_curr_.GetX() - other.pos_curr_.GetX() ) ) * ( ( moving_obj.pos_curr_.GetX() - other.pos_curr_.GetX() ) ) )
            + ( ( ( moving_obj.pos_curr_.GetY() - other.pos_curr_.GetY() ) ) * ( ( moving_obj.pos_curr_.GetY() - other.pos_curr_.GetY() ) ) );
        distance_next = ( ( ( moving_obj.pos_next_.GetX() - other.pos_next_.GetX() ) ) * ( ( moving_obj.pos_next_.GetX() - other.pos_next_.GetX() ) ) )
            + ( ( ( moving_obj.pos_next_.GetY() - other.pos_next_.GetY() ) ) * ( ( moving_obj.pos_next_.GetY() - other.pos_next_.GetY() ) ) );
        if( distance_curr > distance_next )
        {
			log("something updated \n");

			if (moving_velocity_x + other_velocity_x > moving_velocity_x) // i.e. they are heading same direction
			{
				if (moving_velocity_x > other_velocity_x)
				{
					// moving_obj should change direction
					moving_obj.velocity_.SetX(- moving_velocity_x);
					moving_obj.velocity_server_.SetX(- moving_velocity_server_x);
					other.velocity_.SetX(moving_velocity_x + other_velocity_x);
					other.velocity_server_.SetX(moving_velocity_server_x+ other_velocity_server_x);
				}
				else
				{
					moving_obj.velocity_.SetX(moving_velocity_x + other_velocity_x);
					moving_obj.velocity_server_.SetX(moving_velocity_server_x + other_velocity_server_x);
					other.velocity_.SetX(-other_velocity_x);
					other.velocity_server_.SetX(-other_velocity_server_x);
				}
			}
			else
			{
				moving_obj.velocity_.SetX(other_velocity_x);
				moving_obj.velocity_server_.SetX(other_velocity_server_x);
				other.velocity_.SetX(moving_velocity_x);
				other.velocity_server_.SetX(moving_velocity_server_x);
			}
            
			if (moving_velocity_y + other_velocity_y > moving_velocity_y) // i.e. they are heading same direction
			{
				if (moving_velocity_y > other_velocity_y)
				{
					// moving_obj should change direction
					moving_obj.velocity_.SetY(-moving_velocity_y);
					moving_obj.velocity_server_.SetY(-moving_velocity_server_y);
					other.velocity_.SetY(moving_velocity_y + other_velocity_y);
					other.velocity_server_.SetY(moving_velocity_server_y + other_velocity_server_y);
				}
				else
				{
					moving_obj.velocity_.SetY(moving_velocity_y + other_velocity_y);
					moving_obj.velocity_server_.SetY(moving_velocity_server_y + other_velocity_server_y);
					other.velocity_.SetY(-other_velocity_y);
					other.velocity_server_.SetY(-other_velocity_server_y);
				}
			}
			else
			{
				moving_obj.velocity_.SetY(other_velocity_y);
				moving_obj.velocity_server_.SetY(other_velocity_server_y);
				other.velocity_.SetY(moving_velocity_y);
				other.velocity_server_.SetY(moving_velocity_server_y);
			}
        }
		else
		{
			log("gg? \n");
			moving_obj.velocity_.SetX(other_velocity_x);
			moving_obj.velocity_.SetY(other_velocity_y);
			moving_obj.velocity_server_.SetX(other_velocity_server_x);
			moving_obj.velocity_server_.SetY(other_velocity_server_y);
			other.velocity_.SetX(moving_velocity_x);
			other.velocity_.SetY(moving_velocity_y);
			other.velocity_server_.SetX(moving_velocity_server_x);
			other.velocity_server_.SetY(moving_velocity_server_y);
		}
    }
}

// ** CAUTION ** This function is extremely inefficient. Can you try to improve this?
void Application::CheckCollided( Movables &moving_obj, bool ismyship )
{
    // Lab 12. Part 4. Step 1.2 Update the codes of collision checking function
    switch( moving_obj.GetObjectType() )
    {
        case MOVABLE_OBJECT_TYPE_SPACESHIP:
        {
            // Collision check between my ship and enemy ships.
            for( auto itr_enemyship : enemyships_ )
            {
				if (itr_enemyship->GetShipHP() > 0)
				{
					if (HasCollided(moving_obj, *itr_enemyship))
					{
						log("COLLIDED");
						VelocityTransferByCollision(moving_obj, *itr_enemyship);
						if (MOVABLE_OBJECT_TYPE_SPACESHIP == moving_obj.GetObjectType() && ismyship)
						{
							Net::send_packet_collided(*myship_, *itr_enemyship);
						}
					}
				}
            }
        }
        break;

        case MOVABLE_OBJECT_TYPE_ENEMYSHIP:
        {
            // Nothing to do here.
        }
        break;

        case MOVABLE_OBJECT_TYPE_MISSILE:
        {
            // Collision check between my missile and enemy ships.
            for( auto itr_enemyship : enemyships_ )
            {
				if (itr_enemyship->GetShipHP() > 0)
				{
					if (HasCollided(moving_obj, *itr_enemyship))
					{
						Net::send_packet_missilecollided(*mymissile_, MOVABLE_OBJECT_TYPE_ENEMYSHIP, itr_enemyship->GetShipID());
						CreateBoom(
							mymissile_->pos_curr_.GetX(),
							mymissile_->pos_curr_.GetY(),
							mymissile_->pos_curr_.GetAngular(),
							mymissile_->velocity_server_.GetX() * 0.5, //so the booms move at half speed
							mymissile_->velocity_server_.GetY() * 0.5
						);

						delete mymissile_;
						mymissile_ = NULL;
						return; // Missile does not exist anymore. So don't need to process the collision.
					}
				}
            }

            // Collision check between my missile and asteroids.
            for( auto itr_asteroid : asteroids_ )
            {
                if( HasCollided( moving_obj, *itr_asteroid ) )
                {
                    Net::send_packet_missilecollided( *mymissile_, MOVABLE_OBJECT_TYPE_ASTEROID, itr_asteroid->GetID() );
					CreateBoom(
						mymissile_->pos_curr_.GetX(),
						mymissile_->pos_curr_.GetY(),
						mymissile_->pos_curr_.GetAngular(),
						mymissile_->velocity_server_.GetX() * 0.5, //so the booms move at half speed
						mymissile_->velocity_server_.GetY() * 0.5
					);

                    delete mymissile_;
                    mymissile_ = NULL;
                    return; // Missile does not exist anymore. So don't need to process the collision.
                }
            }
        }
        break;
    }

    // Lab 12. Part 4. Step 1.2 Update the codes of collision checking function
    //// 1. collision check between moving object and myship
    //if( MOVABLE_OBJECT_TYPE_SPACESHIP != moving_obj.GetObjectType() )
    //{
    //    if( HasCollided( moving_obj, *myship_ ) )
    //    {
    //        VelocityTransferByCollision( moving_obj, *myship_ );
    //        Net::send_packet_collided( *myship_ );
    //    }
    //}
    //// 2. collision check between moving object and enemyship
    //for( auto itr_enemyship : enemyships_ )
    //{
    //    if( HasCollided( moving_obj, *itr_enemyship ) )
    //    {
    //        VelocityTransferByCollision( moving_obj, *itr_enemyship );
    //        if( MOVABLE_OBJECT_TYPE_SPACESHIP == moving_obj.GetObjectType() )
    //        {
    //            Net::send_packet_collided( *myship_ );
    //        }
    //    }
    //}

    // Lab 12. Part 1. Step 2.3 Remove the collision check for the asteroids in the client
    // 3. collision check between moving object and asteroid
    //for( auto itr_asteroid : asteroids_ )
    //{
    //    if( HasCollided( moving_obj, *itr_asteroid ) )
    //    {
    //        VelocityTransferByCollision( moving_obj, *itr_asteroid );
    //        if( MOVABLE_OBJECT_TYPE_SPACESHIP == moving_obj.GetObjectType() )
    //        {
    //            Net::send_packet_collided( *myship_ );
    //        }
    //    }
    //}
}

Ship * Application::FindEnemyShip( int ShipID )
{
    for( auto enemyship : enemyships_ )
    {
        if( ShipID == enemyship->GetShipID() )
        {
            return enemyship;
        }
    }

    return nullptr;
}
