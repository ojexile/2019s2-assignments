///////////////////////////////////////////////////////////////////////////////
// ** EXAMPLE of how to use NetLib.lib for server application.               //
// You can look around and modify anything.                                  //
// But please follow the guided sequence.                                    //
///////////////////////////////////////////////////////////////////////////////

#include "ServerNetwork.h"
#include "process_received_packet.h"
#include "process_send_packet.h"
#include "ship.h"
#include "asteroid.h"
#include "timebomb.h"
#include "medKit.h"
#include "timer/timer.h"
#include <vector>
#include <cstdlib>
#include <time.h> 

#ifdef _DEBUG
#include <io.h>

void log( const char *szFormat, ... )
{
    char Buff[1024];
    char Msg[1024];
    va_list arg;

    va_start( arg, szFormat );
    _vsnprintf_s( Msg, 1024, szFormat, arg );
    va_end( arg );

    sprintf_s( Buff, 1024, "%s\n", Msg );
    _write( 1, Buff, (unsigned int)strlen( Buff ) );
}
#endif

// Function prototypes.
bool HasCollided_Asteroid( _Asteroid &asteroid, const float collided_object_x, const float collided_object_y, const int collided_object_imagesize );
void VelocityTransfer_AsteroidAndSpaceship( _Asteroid &asteroid, int &ship_id );

// Global variables.
HNet::_ServerNetwork NetObj;
Ship g_ShipList[MAX_CONNECTION + 1]; // Ship list.
Timer g_LoopTimer; // Global object for timer.
int g_ClientScreenWidth = 800;
int g_ClientScreenHeight = 600;
std::vector <_Asteroid *> g_AsteroidList; // Asteroid list.
std::vector <_Timebomb *> g_TimeBombList;
_Medkit* currentMedkit;

float medKitTimer;

bool init_game_server( void )
{ // Initialize whatever you need.

    // Initialize two asteroid. This is for simple example.
	// For Assignment 2, think about how you can increase this and also to randomize it 
	// i.e. Asteroids should spawn in random locations
	// There should be a random number of starting asteroids (i.e. between 4-8 asteroids)
    g_AsteroidList.push_back( new _Asteroid( 1, 100, 100, 1 ) );
    g_AsteroidList.push_back( new _Asteroid( 2, 700, 500, 1 ) );

	medKitTimer = NULL;
	srand(time(NULL));
    return true;
}

int main( void )
{
    if( false == init_game_server() )
    {
        return 0;
    }

    if( false == NetObj.InitNet( HNet::APPTYPE_SERVER, HNet::PROTOCOL_TCP, 3456 ) )
    {
#ifdef _DEBUG
        log( "%s", NetObj.GetErrorMessage() );
#endif
        return 0;
    }
#ifdef _DEBUG
    log( "Server network initialized!" );
    log( "Network thread started! Ready to accept & receive the message." );
#endif

    // Update the asteroid movement.
    float time_delta = g_LoopTimer.GetTimer_sec();

    Sleep( 1000 ); // Wait for a while to make sure everything is ok.

    struct HNet::_ProcessSession *ToProcessSession;

    while( 1 )
    {
        while( nullptr != ( ToProcessSession = NetObj.GetProcessList()->GetFirstSession() ) )
        {
            switch( ToProcessSession->SessionState )
            {
                case HNet::SESSION_STATE_NEWCONNECTION:
                { // New connection request arrived.
#ifdef _DEBUG
                    log( "New connection connected: Index:%d. Total Connection now:%d", ToProcessSession->SessionIndex, NetObj.GetConnectedCount() );
#endif
                    SendPacket_NewAccept( ToProcessSession->SessionIndex );
                }
                    break;

                case HNet::SESSION_STATE_CLOSEREDY:
                { // Connection closed arrived or communication error.
#ifdef _DEBUG
                    log( "Received: Index %d wants to close or already closed.\nTotal Connection now:%d", ToProcessSession->SessionIndex, NetObj.GetConnectedCount() );
#endif
                    SendPacketProcess_DisconnectEnemyShip( ToProcessSession->SessionIndex );
                }
                    break;

                case HNet::SESSION_STATE_READPACKET:
                { // Any packet data recevied.
                    ProcessReceivedPacket( ToProcessSession );
                }
                    break;

                default:
                    break;
            }

            NetObj.GetProcessList()->DeleteFirstSession();
        }

        //////////////////////////////////////////////////////////////////////////
        // You can add your own server codes here. If there is any regular work.

        float asteroid_prev_x, asteroid_prev_y;
        float time_delta = g_LoopTimer.GetTimer_sec();
//        for( auto asteroid : g_AsteroidList )

		if (!currentMedkit)
		{
			medKitTimer -= time_delta;
			if (medKitTimer <= 0)
			{
				float randX = rand() % g_ClientScreenWidth;
				float randY = rand() % g_ClientScreenHeight;

				currentMedkit = new _Medkit(-1, randX, randY);
				medKitTimer = 5;

				SendPacketProcess_MedKitSpawned(*currentMedkit);
			}
		}

        for( auto asteroid = g_AsteroidList.begin(); asteroid != g_AsteroidList.end(); ++asteroid )
        {
            asteroid_prev_x = (*asteroid)->GetX();
            asteroid_prev_y = (*asteroid)->GetY();
            (*asteroid)->Update( time_delta, 30, 30 );
			(*asteroid)->lastnetworkupdate += time_delta;
		
            if( (asteroid_prev_x != (*asteroid)->GetX()) || (asteroid_prev_y != (*asteroid)->GetY()) )
            {
				// lastnetworkupdate is a simple check that makes sure each asteroid only sends an update about once every second
				// you can experiment with this number to find which frequency works best for you
				if ((*asteroid)->lastnetworkupdate >= 1.0f)
				{				
					SendPacketProcess_AsteroidMovement(*(*asteroid));
					(*asteroid)->lastnetworkupdate = 0.0f;
				}
            }

            // Lab 12. Part 1. Step 1.3 Add collision checking codes in the server
            // Collision check between asteroid and spaceship
            for( int ship_id = 1; ship_id < (MAX_CONNECTION + 1); ++ship_id )
            {
                if( false == g_ShipList[ship_id].connected ) continue;

				//need to update the ship simulation here since we aren't spamming packets (extrapolate)
				g_ShipList[ship_id].x += g_ShipList[ship_id].velocity_server_x * time_delta;
				g_ShipList[ship_id].y += g_ShipList[ship_id].velocity_server_y * time_delta;

                if( HasCollided_Asteroid( *(*asteroid), g_ShipList[ship_id].x, g_ShipList[ship_id].y, g_ShipList[ship_id].image_size ) )
                {
                    VelocityTransfer_AsteroidAndSpaceship( *(*asteroid), ship_id );
                    SendPacketProcess_AsteroidCollidedWithShip( *(*asteroid), ship_id );
                }
            }
            // Collision check between asteroid and asteroid
            //for( auto next_asteroid = (asteroid + 1); next_asteroid != g_AsteroidList.end(); ++next_asteroid )
            //{
            //    if( HasCollidedAsteroid( *(*asteroid), (*next_asteroid)->GetX(), (*next_asteroid)->GetY(), (*next_asteroid)->GetImageSize ) )
            //    {
            //        VelocityTrasnfer_AsteroidAndAsteroid( *(*asteroid), *(*next_asteroid) );
            //        SendPacketProcess_AsteroidCollidedWithAsteroid( *(*asteroid), *(*next_asteroid) );
            //    }
            //}
        }

		for (int i = 0; i < g_TimeBombList.size();)
		{
			_Timebomb* timebomb = g_TimeBombList[i];

			SendPacketProcess_TimebombTimer(*timebomb);

			if (timebomb->GetTimer() <= 0)
				g_TimeBombList.erase(g_TimeBombList.begin() + i);
			else
			{
				timebomb->lastnetworkupdate += time_delta;
				timebomb->Update(time_delta);				
				++i;
			}			
		}

        Sleep( 50 ); //sleep 100 is too slow, 50?
    }

    return 0;
}

// Lab 12. Part 1. Step 1.4 Add collision checking codes in the server
// do note that the collision codes here is very rudimentary and doesn't have the benefit of HGE collision checking
// a better way would be to re-write the server with the HGE engine. If you choose to attempt this, it can be considered as a network feature improvement
bool HasCollided_Asteroid( _Asteroid &asteroid, const float collided_object_x, const float collided_object_y, const int collided_object_imagesize )
{
    // Check the collision by distance.
    int colliding_distance = (asteroid.GetImageSize() / 2) + (collided_object_imagesize / 2);
    int distance = static_cast<int>( ((asteroid.GetX() - collided_object_x) * (asteroid.GetX() - collided_object_x))
                                   + ((asteroid.GetY() - collided_object_y) * (asteroid.GetY() - collided_object_y)) );
    if( (colliding_distance * colliding_distance) > distance )
    { // Collided!
#ifdef _DEBUG
        log( "### Asteroid has collided! ### AsteroidID:%d", asteroid.GetID() );
        log( "    --> CollidingDistance:%d, distance:%d", (colliding_distance * colliding_distance), distance );
#endif
        return true;
    }

    return false;
}

// Lab 12. Part 1. Step 1.5 Add collision checking codes in the server
void VelocityTransfer_AsteroidAndSpaceship( _Asteroid &asteroid, int &ship_id )
{
    float asteroid_velocity_x = asteroid.GetVelocityX();
    float asteroid_velocity_y = asteroid.GetVelocityY();
    float ship_velocity_x = g_ShipList[ship_id].velocity_server_x;
    float ship_velocity_y = g_ShipList[ship_id].velocity_server_y;

    if( (0.0f == ship_velocity_x) && (0.0f == ship_velocity_y) )
    {
        asteroid.SetVelocityX( (-asteroid_velocity_x) * 0.5f );
        asteroid.SetVelocityY( (-asteroid_velocity_y) * 0.5f );
        g_ShipList[ship_id].velocity_server_x = asteroid_velocity_x * 0.5f;
        g_ShipList[ship_id].velocity_server_y = asteroid_velocity_y * 0.5f;
    }
    if( (0.0f == asteroid_velocity_x) && (0.0f == asteroid_velocity_y) )
    {
        asteroid.SetVelocityX( ship_velocity_x * 0.5f );
        asteroid.SetVelocityY( ship_velocity_y * 0.5f );
        g_ShipList[ship_id].velocity_server_x = (-ship_velocity_x) * 0.5f;
        g_ShipList[ship_id].velocity_server_y = (-ship_velocity_y) * 0.5f;
    }
    else
    {
        float distance_curr = ((asteroid.GetX() - g_ShipList[ship_id].x) * (asteroid.GetX() - g_ShipList[ship_id].x))
                            + ((asteroid.GetY() - g_ShipList[ship_id].y) * (asteroid.GetY() - g_ShipList[ship_id].y));

        float asteroid_next_x = asteroid.GetX() + (asteroid.GetVelocityX() * 0.1f);
        float asteroid_next_y = asteroid.GetY() + (asteroid.GetVelocityY() * 0.1f);
        float ship_next_x = g_ShipList[ship_id].x + (g_ShipList[ship_id].velocity_server_x * 0.1f);
        float ship_next_y = g_ShipList[ship_id].y + (g_ShipList[ship_id].velocity_server_y * 0.1f);
        float distance_next = ((asteroid_next_x - ship_next_x) * (asteroid_next_x - ship_next_x))
                            + ((asteroid_next_y - ship_next_y) * (asteroid_next_y - ship_next_y));

        if( distance_curr > distance_next )
        {
            asteroid.SetVelocityX( ship_velocity_x * 0.8f );
            asteroid.SetVelocityY( ship_velocity_y * 0.8f );
            g_ShipList[ship_id].velocity_server_x = asteroid_velocity_x * 0.8f;
            g_ShipList[ship_id].velocity_server_y = asteroid_velocity_y * 0.8f;
        }
    }
}

