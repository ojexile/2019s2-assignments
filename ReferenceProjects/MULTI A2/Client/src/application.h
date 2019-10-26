#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "movables/ship.h"
#include "movables/asteroid.h"
#include "movables/missile.h"
#include "movables/boom.h"
#include "movables/Timebomb.h"
#include "movables/Explosion.h"
#include "movables/medKit.h"
#include <vector>

enum _GAMESTATE
{
    GAMESTATE_NONE = 0,
    GAMESTATE_INITIALIZING,
    GAMESTATE_INPLAY,
    GAMESTATE_QUITGAME
};

//! The default angular velocity of the ship when it is in motion
static const float DEFAULT_ANGULAR_VELOCITY = 3.0f;
//! The default acceleration of the ship when powered
static const float DEFAULT_ACCELERATION = 50.0f;

/**
* The application class is the main body of the program. It will
* create an instance of the graphics engine and execute the
* Update/Render cycle.
*
*/
class Application
{
    HGE *hge_; // Instance of the internal graphics engine

    Ship *myship_; // My own space ship

    typedef std::vector<Ship*> ShipList;  // A list of ships
    ShipList enemyships_; // List of all the enemy ships in the universe

    typedef std::vector<Asteroid*> AsteroidList; // A list of asteroids
    AsteroidList asteroids_; // List of all the asteroids in the universe

	typedef std::vector<Timebomb *> TimebombList; // A list of asteroids
	TimebombList timebombs_;
	Timebomb *myTimebomb;

    // Lab 12. Part 2. Step 3. Add missile data structure into your Application class
    Missile *mymissile_;
    bool have_missile;
    bool keydown_space;
	bool keydown_b;

    // Lab 12. Part 3. Step 4.1 Add the new vector to contain the enemy missiles
    typedef std::vector <Missile *> MissileList;
    MissileList enemymissiles_;

	typedef std::vector <Boom*> BoomList;
	BoomList booms_;

	typedef std::vector <Explosion*> ExplosionList;
	ExplosionList explosions_;

	Medkit* spawnedMedkit;

    bool Init();
    static bool Loop();
    void Shutdown();

    private:
        int gamestate_;
		float networkidletime_;
		float screenWidth, screenHeight;
		std::unique_ptr<hgeFont> font;

    public:
        void SetGameState( int gamestate ) { gamestate_ = gamestate; }
        int  GetGameState( void          ) { return gamestate_;      }

    public:
        Application();
        ~Application() throw( );

        void Start();
        bool Update();
        void Render();

		void CreateTimebomb(float x, float y, int id);
		void CreateExplosion(float x, float y);
        void CreateMissile( float x, float y, float w, int id );
		void CreateBoom(float x, float y, float w, float vel_x, float vel_y);

        template <typename T1, typename T2>
        bool HasCollided( T1 &object, T2 &movable );

        template <typename Mov, typename Tgt>
        void VelocityTransferByCollision( Mov &moving_obj, Tgt &other );

        void CheckCollided( Movables &moving_obj, bool ismyship );

    public:
        Ship*         GetMyShip          ( void ) { return myship_;         }
        ShipList*     GetEnemyShipList   ( void ) { return &enemyships_;    }
        AsteroidList* GetAsteroidList    ( void ) { return &asteroids_;     }
        // Lab 12. Part 3. Step 4.1 Add the new vector to contain the enemy missiles
        MissileList*  GetEnemyMissileList( void ) { return &enemymissiles_; }
		BoomList*  GetBoomList(void) { return &booms_; }
		Timebomb*  GetMyTimebomb(void) { return myTimebomb; }
		Medkit*  GetMyMedkit(void) { return spawnedMedkit; }
		void  SetMyMedkit(Medkit* _input) { spawnedMedkit = _input; }
		TimebombList*  GetTimebombList(void) { return &timebombs_; }
		bool ServerFull;

        Ship* FindEnemyShip( int ShipID );
};

#endif