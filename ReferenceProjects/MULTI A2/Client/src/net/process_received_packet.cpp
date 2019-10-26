#include "ClientNetwork.h"
#include "packets/packets_s2c.h"
#include "process_received_packet.h"
#include "process_send_packet.h"
#include "globals.h"


#ifdef _DEBUG
extern void log( char *szFormat, ... );
#endif


namespace Net {
    void ProcessReceviedPacket( Application &thisapp )
    {
        // Check any message from network! You can try to make this message processing
        // with another thread but be careful with synchronization.
        // HNet Step 4. Prepare the pointer of _ProcessSession and buffer structure of _PacketMessage.
        //              _ProcessSession pointer will give you the session information
        //              if there is any network communication from any client.
        //              _PacketMessage is for fetch the each of the actual data inside the packet buffer.
        struct HNet::_ProcessSession *ToProcessSession;

        // HNet Step 5. Message Loop. Check any message from server and process.
        while( nullptr != ( ToProcessSession = Global::NetObj.GetProcessList()->GetFirstSession() ) )
        { // Something received from network.
            int PacketID;

            ToProcessSession->PacketMessage >> PacketID;
            switch( PacketID )
            {
                case PACKET_ID_S2C_WELCOMEMESSAGE:
                { // If client received Welcome Message from server, find out the SessionID (= ShipID).
                    ProcessReceivedPacket_WelcomeMessage( thisapp, *ToProcessSession );
                }
                break;

                case PACKET_ID_S2C_ENTERGAMEOK:
                {
                    thisapp.SetGameState( GAMESTATE_INPLAY );
                }
                break;

                case PACKET_ID_S2C_ENEMYSHIP:
                case PACKET_ID_S2C_NEWENEMYSHIP:
                {
                    ProcessReceivedPacket_NewEnemyShip( thisapp, *ToProcessSession );
                }
                break;

                case PACKET_ID_S2C_NEWASTEROID:
                {
                    ProcessReceivedPacket_NewAstreroid( thisapp, *ToProcessSession );
                }
                break;

                case PACKET_ID_S2C_DISCONNECTEDENEMYSHIP:
                {
                    ProcessReceivedPacket_DisconnectedEnemyShip( thisapp, *ToProcessSession );
                }
                break;

                case PACKET_ID_S2C_MOVEMENT:
                {
                    ProcessReceivedPacket_Movement( thisapp, *ToProcessSession );
                }
                break;

                case PACKET_ID_S2C_COLLIDED:
                {
                    ProcessReceviedPacket_Collided( thisapp, *ToProcessSession );
                }
                break;

                case PACKET_ID_S2C_ASTEROIDMOVEMENT:
                {
                    ProcessReceivedPacket_AsteroidMovement( thisapp, *ToProcessSession );
                }
                break;

                // Lab 12. Part 1. Step 2.1 Receive the asteroid collided information and update the asteroid in the client
                case PACKET_ID_S2C_ASTEROIDCOLLIDED:
                {
                    ProcessReceivedPacket_AsteroidCollided( thisapp, *ToProcessSession );
                }
                break;

                // Lab 12. Part 3. Step 4.2 Add the codes to receive the new missile packet
                case PACKET_ID_S2C_NEWMISSILE:
                {
                    ProcessReceivedPacket_NewMissile( thisapp, *ToProcessSession );
                }
                break;

                // Lab 12. Part 4. Step 5. Receive the packet and delete the missile
                case PACKET_ID_S2C_MISSILECOLLIDED:
                {
                    ProcessReceivedPacket_MissileCollided( thisapp, *ToProcessSession );
                }
                break;

				case PACKET_ID_S2C_SERVERFULL:
				{
					thisapp.ServerFull = true;
				}
				break;

				case PACKET_ID_S2C_NEWTIMEBOMB:
				{
					ProcessReceivedPacket_NewTimebomb(thisapp, *ToProcessSession);
				}
				break;

				case PACKET_ID_S2C_TIMEBOMBTIMER:
				{
					ProcessReceivedPacket_TimebombTimer(thisapp, *ToProcessSession);
				}
				break;

				case PACKET_ID_S2C_NEWMEDKIT:
				{
					ProcessReceivedPacket_NewMedkit(thisapp, *ToProcessSession);
				}
				break;

				case PACKET_ID_S2C_MEDKIT_TAKEN:
				{
					ProcessReceivedPacket_MedkitTaken(thisapp, *ToProcessSession);
				}
				break;
            }

            // HNet Step 6. After finish the process with packet, You should delete the session message.
            //              If you forget to delete, it will cause memory leak!
            Global::NetObj.GetProcessList()->DeleteFirstSession();
        }
    }

    void ProcessReceivedPacket_WelcomeMessage( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        struct PKT_S2C_WelcomeMessage PacketData;
        ToProcessSession.PacketMessage >> PacketData;
        thisapp.GetMyShip()->SetShipID( PacketData.ShipID );
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_WELCOMEMESSAGE. ShipID:%d", PacketData.ShipID );
#endif

        // Send my spaceship info to the server for synchronization.
        Net::send_packet_enter_game( *(thisapp.GetMyShip()) );
    }

    void ProcessReceivedPacket_NewEnemyShip( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        //struct PKT_S2C_EnemyShip EnemyshipPacketData;
        struct PKT_S2C_NewEnemyShip NewEnemyShipPacketData;

        ToProcessSession.PacketMessage >> NewEnemyShipPacketData;

        std::string EnemyShipName = "Enemy" + std::to_string( NewEnemyShipPacketData.ShipID );
        Ship *EnemyShip = new Ship( NewEnemyShipPacketData.ShipType, EnemyShipName,
                                    NewEnemyShipPacketData.x, NewEnemyShipPacketData.y, 0.0f );

        EnemyShip->SetShipID( NewEnemyShipPacketData.ShipID );
        EnemyShip->SetShipName( EnemyShipName );
        EnemyShip->SetShipType( NewEnemyShipPacketData.ShipType );
        EnemyShip->pos_curr_.SetX( NewEnemyShipPacketData.x );
        EnemyShip->pos_curr_.SetY( NewEnemyShipPacketData.y );
        EnemyShip->pos_curr_.SetAngular( NewEnemyShipPacketData.angular );
        EnemyShip->SetObjectType( MOVABLE_OBJECT_TYPE_ENEMYSHIP );
		EnemyShip->SetShipHP(NewEnemyShipPacketData.hp);
		EnemyShip->SetShipDeathTimer(NewEnemyShipPacketData.deathTimer);

        thisapp.GetEnemyShipList()->push_back( EnemyShip );
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_ENEMYSHIP or PACKET_ID_S2C_NEWENEMYSHIP. ShipID:%d", EnemyShip->GetShipID() );
        log( "        - ShipName:%s, Type:%d, x:%0.2f, y:%0.2f, w:%0.2f",
             EnemyShip->GetShipName().c_str(), EnemyShip->GetShipType(), EnemyShip->pos_curr_.GetX(), EnemyShip->pos_curr_.GetY(), EnemyShip->pos_curr_.GetAngular() );
        log( "Now I have: " );
        for( auto Enemy : *(thisapp.GetEnemyShipList()) )
        {
            log( "%d ", Enemy->GetShipID() );
        }
#endif
    }

    void ProcessReceivedPacket_NewAstreroid( Application &thisapp, struct HNet::_ProcessSession &ToProcessSessoin )
    {
        struct PKT_S2C_NewAsteroid AsteroidData;
        ToProcessSessoin.PacketMessage >> AsteroidData;
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_NEWASTEROID. ID:%d, vx:%0.2f, vy:%0.2f", AsteroidData.AsteroidID, AsteroidData.velocity_x, AsteroidData.velocity_y );
#endif

        Asteroid *asteroid = new Asteroid( "asteroid.png", AsteroidData.x, AsteroidData.y,
                                           AsteroidData.velocity_angular );
        asteroid->SetID( AsteroidData.AsteroidID );
        asteroid->velocity_.SetX( AsteroidData.velocity_x );
        asteroid->velocity_.SetY( AsteroidData.velocity_y );
        asteroid->velocity_.SetAngular( AsteroidData.velocity_angular );
        thisapp.GetAsteroidList()->push_back( asteroid );
    }

    void ProcessReceivedPacket_DisconnectedEnemyShip( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        struct PKT_S2C_EnemyShipDisconnect EnemyShipData;
        ToProcessSession.PacketMessage >> EnemyShipData;

        for( unsigned int i = 0; i < thisapp.GetEnemyShipList()->size(); ++i )
        {
            if( thisapp.GetEnemyShipList()->at( i )->GetShipID() == EnemyShipData.ShipID )
            {
                thisapp.GetEnemyShipList()->erase( thisapp.GetEnemyShipList()->begin() + i );

                // Lab 12. Part 3. Step 6. Delete the missile when the enemy spaceship leaves the game
                // If there is existing missile with the ShipID, delete it.
                for( unsigned int i = 0; i < thisapp.GetEnemyMissileList()->size(); ++i )
                {
                    if( thisapp.GetEnemyMissileList()->at( i )->GetOwnerID() == EnemyShipData.ShipID )
                    {
						Missile *temp = thisapp.GetEnemyMissileList()->at(i);

							thisapp.CreateBoom(
								temp->pos_curr_.GetX(),
								temp->pos_curr_.GetY(),
								temp->pos_curr_.GetAngular(),
								temp->velocity_server_.GetX() * 0.5, //so the booms move at half speed
								temp->velocity_server_.GetY() * 0.5
							);

                        thisapp.GetEnemyMissileList()->erase( thisapp.GetEnemyMissileList()->begin() + i );
                        break;
                    }
                }

                break;
            }
        }
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_DISCONNECT. ShipID: %d", EnemyShipData.ShipID );
        log( "Now I have: " );
        for( auto Enemy : *(thisapp.GetEnemyShipList()) )
        {
            log( "%d ", Enemy->GetShipID() );
        }
#endif
    }

    void ProcessReceivedPacket_Movement( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        struct PKT_S2C_Movement MovementData;
        ToProcessSession.PacketMessage >> MovementData;
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_MOVEMENT. ShipID:%d, x:%0.2f, y:%0.2f, a:%0.2f, vx:%0.2f, vy:%0.2f, vsx:%0.2f, vsy:%0.2f, va:%0.2f",
             MovementData.ShipID, MovementData.x, MovementData.y, MovementData.angular,
             MovementData.velocity_x, MovementData.velocity_y, MovementData.velocity_server_x, MovementData.velocity_server_y, MovementData.velocity_angular );
#endif

        if( thisapp.GetMyShip()->GetShipID() == MovementData.ShipID )
        {
            return;
        }

        // Update enemyship.
        Ship *MoveShip = thisapp.FindEnemyShip( MovementData.ShipID );
        MoveShip->pos_server_.SetX( MovementData.x );
        MoveShip->pos_server_.SetY( MovementData.y );
        MoveShip->pos_server_.SetAngular( MovementData.angular );
        MoveShip->velocity_.SetX( MovementData.velocity_x );
        MoveShip->velocity_.SetY( MovementData.velocity_y );
        MoveShip->velocity_.SetAngular( MovementData.velocity_angular );
        MoveShip->velocity_server_.SetX( MovementData.velocity_server_x );
        MoveShip->velocity_server_.SetY( MovementData.velocity_server_y );
		MoveShip->SetShipHP(MovementData.hp);
		MoveShip->SetShipDeathTimer(MovementData.deathTimer);
    }

    void ProcessReceviedPacket_Collided( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        struct PKT_S2C_Collided CollidedData;
        ToProcessSession.PacketMessage >> CollidedData;
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_COLLIDED. ShipID:%d, sx:%0.2f, sy:%0.2f, sa:%0.2f, vx:%0.2f, vy:%0.2f, vsx:%0.2f, vsy:%0.2f, vsa:%0.2f",
             CollidedData.ShipID, CollidedData.x, CollidedData.y, CollidedData.angular, CollidedData.velocity_x, CollidedData.velocity_y,
             CollidedData.velocity_server_x, CollidedData.velocity_server_y, CollidedData.velocity_angular );
#endif

        Ship *CollidedShip = 0;
        if( thisapp.GetMyShip()->GetShipID() == CollidedData.ShipID )
        { // Update my ship.
            CollidedShip = thisapp.GetMyShip();
			// someone collided with me?			
        }
        else
        {
            CollidedShip = thisapp.FindEnemyShip( CollidedData.ShipID );
        }

		// For network functions dealing with pointers, always remember to handle null pointers. If not, code will crash 
		if (CollidedShip == NULL) return;

     //   CollidedShip->pos_server_.SetX( CollidedData.x );
     //   CollidedShip->pos_server_.SetY( CollidedData.y );
        CollidedShip->pos_server_.SetAngular( CollidedData.angular );
        CollidedShip->velocity_.SetX( CollidedData.velocity_x );
        CollidedShip->velocity_.SetY( CollidedData.velocity_y );
        CollidedShip->velocity_server_.SetX( CollidedData.velocity_server_x );
        CollidedShip->velocity_server_.SetY( CollidedData.velocity_server_y );
        CollidedShip->velocity_server_.SetAngular( CollidedData.velocity_angular );		
		CollidedShip->SetShipHP(CollidedData.hp - 1);

		if (CollidedShip->GetShipHP() <= 0)
			CollidedShip->SetShipDeathTimer(5);
    }

    void ProcessReceivedPacket_AsteroidMovement( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        struct PKT_S2C_AsteroidMovement AsteroidMovementData;
        ToProcessSession.PacketMessage >> AsteroidMovementData;
#ifdef _DEBUG
        log( "Received: PACKET_ID_S2C_ASTEROIDMOVEMENT: AsteroidID:%d, x:%0.2f, y:%0.2f, vx:%0.2f, vy:%0.2f, a:%0.2f",
             AsteroidMovementData.AsteroidID, AsteroidMovementData.server_x, AsteroidMovementData.server_y,
             AsteroidMovementData.velocity_x, AsteroidMovementData.velocity_y, AsteroidMovementData.velocity_angular );
#endif

        Asteroid *MovingAsteroid = nullptr;
        for( auto itr_asteroid : *(thisapp.GetAsteroidList()) )
        {
            if( itr_asteroid->GetID() == AsteroidMovementData.AsteroidID )
            {
                MovingAsteroid = itr_asteroid;
            }
        }
        if( nullptr == MovingAsteroid )
        { // ID error. I cannot find this asteroid.
            return;
        }

        // Now, let's update the data.
        MovingAsteroid->pos_server_.SetX( AsteroidMovementData.server_x );
        MovingAsteroid->pos_server_.SetY( AsteroidMovementData.server_y );
        MovingAsteroid->velocity_.SetX( AsteroidMovementData.velocity_x );
        MovingAsteroid->velocity_.SetY( AsteroidMovementData.velocity_y );
        MovingAsteroid->velocity_server_.SetX( AsteroidMovementData.velocity_x );
        MovingAsteroid->velocity_server_.SetY( AsteroidMovementData.velocity_y );
    }

    // Lab 12. Part 1. Step 2.2 Receive the asteroid collided information and update the asteroid in the client
    void ProcessReceivedPacket_AsteroidCollided( Application &thisapp, struct HNet::_ProcessSession &ToProsessSession )
    {
        struct PKT_S2C_AsteroidCollided AsteroidCollidedData;
        ToProsessSession.PacketMessage >> AsteroidCollidedData;

        Asteroid *CollidedAsteroid = NULL;
        for( auto itr_asteroid : *(thisapp.GetAsteroidList()) )
        {
            if( itr_asteroid->GetID() == AsteroidCollidedData.asteroid.id)
            {
                CollidedAsteroid = itr_asteroid;
            }
        }
        if( NULL == CollidedAsteroid )
        { // ID error. I cannot find this asteroid.
            return;
        }

        // Now, let's update the data.
        CollidedAsteroid->pos_curr_.SetX( AsteroidCollidedData.asteroid.x );
        CollidedAsteroid->pos_curr_.SetY( AsteroidCollidedData.asteroid.y );
        CollidedAsteroid->velocity_.SetX( AsteroidCollidedData.asteroid.velocity_x );
        CollidedAsteroid->velocity_.SetY( AsteroidCollidedData.asteroid.velocity_y );

        switch( AsteroidCollidedData.collided_object.type )
        {
            case OBJECT_TYPE_SPACESHIP :
            {
                Ship *CollidedShip;
                if( thisapp.GetMyShip()->GetShipID() == AsteroidCollidedData.collided_object.id )
                {
                    CollidedShip = thisapp.GetMyShip();
                }
                else
                {
                    CollidedShip = thisapp.FindEnemyShip( AsteroidCollidedData.collided_object.id );
                }
                CollidedShip->pos_server_.SetX( AsteroidCollidedData.collided_object.x );
                CollidedShip->pos_server_.SetY( AsteroidCollidedData.collided_object.y );
                CollidedShip->pos_server_.SetAngular( AsteroidCollidedData.collided_object.angular );
                CollidedShip->velocity_.SetAngular( AsteroidCollidedData.collided_object.velocity_angular );
                CollidedShip->velocity_server_.SetX( AsteroidCollidedData.collided_object.velocity_server_x );
                CollidedShip->velocity_server_.SetY( AsteroidCollidedData.collided_object.velocity_server_y );
				CollidedShip->SetShipHP(CollidedShip->GetShipHP() - 1);

				if (CollidedShip->GetShipHP() <= 0)
					CollidedShip->SetShipDeathTimer(5);
            }
            break;

            case OBJECT_TYPE_ASTEROID:
            {
            }
            break;
        }
    }

    // Lab 12. Part 3. Step 4.3. Implement the ProcessReceivedPacket_NewMissile() function
    void ProcessReceivedPacket_NewMissile( Application &thisapp, struct HNet::_ProcessSession &ToProsessSession )
    {
        struct PKT_S2C_NewMissile NewMissileData;
        ToProsessSession.PacketMessage >> NewMissileData;

        // If the missile is my own missile, then ignore the packet.
        if( thisapp.GetMyShip()->GetShipID() == NewMissileData.OwnerShipID ) return;

        // If there is existing missile with the ShipID, delete it first.
        for( unsigned int i = 0; i < thisapp.GetEnemyMissileList()->size(); ++i )
        {
            if( thisapp.GetEnemyMissileList()->at( i )->GetOwnerID() == NewMissileData.OwnerShipID )
            {
				Missile *temp = thisapp.GetEnemyMissileList()->at(i);

				thisapp.CreateBoom(
					temp->pos_curr_.GetX(),
					temp->pos_curr_.GetY(),
					temp->pos_curr_.GetAngular(),
					temp->velocity_server_.GetX() * 0.5, //so the booms move at half speed
					temp->velocity_server_.GetY() * 0.5
				);

                thisapp.GetEnemyMissileList()->erase( thisapp.GetEnemyMissileList()->begin() + i );
                break;
            }
        }

        Missile *missile = new Missile( NewMissileData.x, NewMissileData.y, NewMissileData.angular, NewMissileData.OwnerShipID );
        missile->velocity_.SetX( NewMissileData.velocity_server_x );
        missile->velocity_.SetY( NewMissileData.velocity_server_y );
        missile->velocity_server_.SetX( NewMissileData.velocity_server_x );
        missile->velocity_server_.SetY( NewMissileData.velocity_server_y );
        thisapp.GetEnemyMissileList()->push_back( missile );
    }

    // Lab 12. Part 4. Step 5. Receive the packet and delete the missile
    void ProcessReceivedPacket_MissileCollided( Application &thisapp, struct HNet::_ProcessSession &ToProcessSession )
    {
        struct PKT_S2C_MissileCollided MissileCollidedData;
        ToProcessSession.PacketMessage >> MissileCollidedData;      

		if (thisapp.GetMyShip()->GetShipID() == MissileCollidedData.collided_object.id)
		{
			thisapp.GetMyShip()->SetShipHP(thisapp.GetMyShip()->GetShipHP() - 1);

			if(thisapp.GetMyShip()->GetShipHP() <= 0)
				thisapp.GetMyShip()->SetShipDeathTimer(5);
		}			
		else
		{
			for (int i = 0; i < thisapp.GetEnemyShipList()->size(); ++i)
			{
				Ship* enemyShip = thisapp.GetEnemyShipList()->at(i);
				if (enemyShip->GetShipID() == MissileCollidedData.collided_object.id)
				{
					enemyShip->SetShipHP(enemyShip->GetShipHP() - 1);
					break;
				}					
			}
		}

		// If the missile is my own missile, then ignore the packet.
		if (thisapp.GetMyShip()->GetShipID() == MissileCollidedData.missile.OwnerShipID) return;

        // If there is existing missile with the ShipID, delete it.
        for( unsigned int i = 0; i < thisapp.GetEnemyMissileList()->size(); ++i )
        {
            if( thisapp.GetEnemyMissileList()->at( i )->GetOwnerID() == MissileCollidedData.missile.OwnerShipID )
            {
				Missile *temp = thisapp.GetEnemyMissileList()->at(i);

				thisapp.CreateBoom(
					temp->pos_curr_.GetX(),
					temp->pos_curr_.GetY(),
					temp->pos_curr_.GetAngular(),
					temp->velocity_server_.GetX() * 0.5, //so the booms move at half speed
					temp->velocity_server_.GetY() * 0.5
				);

                thisapp.GetEnemyMissileList()->erase( thisapp.GetEnemyMissileList()->begin() + i );
                break;
            }
        }
    }

	void ProcessReceivedPacket_NewTimebomb(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession)
	{
		struct PKT_S2C_NewTimebomb NewTimebombData;
		ToProsessSession.PacketMessage >> NewTimebombData;

		// If the missile is my own missile, then ignore the packet.
		if (thisapp.GetMyShip()->GetShipID() == NewTimebombData.OwnerShipID) return;

		Timebomb *timebomb = new Timebomb(NewTimebombData.x, NewTimebombData.y, NewTimebombData.OwnerShipID);
		thisapp.GetTimebombList()->push_back(timebomb);
	}

	void ProcessReceivedPacket_TimebombTimer(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession)
	{
		struct PKT_S2C_TimebombTimer TimebombTimerData;
		ToProsessSession.PacketMessage >> TimebombTimerData;		

		if (TimebombTimerData.OwnerShipID == thisapp.GetMyShip()->GetShipID())
		{
			thisapp.GetMyTimebomb()->SetTimer(TimebombTimerData.timer);
		}
		else
		{
			for (int i = 0; i < thisapp.GetTimebombList()->size(); ++i)
			{
				if (thisapp.GetTimebombList()->at(i)->GetOwnerID() == TimebombTimerData.OwnerShipID)
				{
					thisapp.GetTimebombList()->at(i)->SetTimer(TimebombTimerData.timer);
					break;
				}
			}
		}

		if (TimebombTimerData.timer <= 0)
		{	
			thisapp.CreateExplosion(TimebombTimerData.x, TimebombTimerData.y);

			for (int i = 0; i < thisapp.GetEnemyShipList()->size(); ++i)
			{
				if (thisapp.GetEnemyShipList()->at(i)->GetShipID() == TimebombTimerData.OwnerShipID)
				{
					for (int j = 0; j < thisapp.GetTimebombList()->size(); ++j)
					{
						if (thisapp.GetTimebombList()->at(j)->GetOwnerID() == thisapp.GetEnemyShipList()->at(i)->GetShipID())
						{
							thisapp.GetTimebombList()->erase(thisapp.GetTimebombList()->begin() + j);
							break;
						}						
					}					
				}
				else
				{
					Ship* enemyShip = thisapp.GetEnemyShipList()->at(i);
					float distance = (enemyShip->pos_curr_.GetX() - TimebombTimerData.x) * (enemyShip->pos_curr_.GetX() - TimebombTimerData.x) + (enemyShip->pos_curr_.GetY() - TimebombTimerData.y) * (enemyShip->pos_curr_.GetY() - TimebombTimerData.y);

					if (distance < 256 * 256)
						enemyShip->SetShipHP(enemyShip->GetShipHP() - 2);
				}
			}

			if (TimebombTimerData.OwnerShipID != thisapp.GetMyShip()->GetShipID())
			{
				Ship* myShip = thisapp.GetMyShip();
				float distance = (myShip->pos_curr_.GetX() - TimebombTimerData.x) * (myShip->pos_curr_.GetX() - TimebombTimerData.x) + (myShip->pos_curr_.GetY() - TimebombTimerData.y) * (myShip->pos_curr_.GetY() - TimebombTimerData.y);

				if (distance < 256 * 256)
				{
					myShip->SetShipHP(myShip->GetShipHP() - 2);
					if (thisapp.GetMyShip()->GetShipHP() <= 0)
						thisapp.GetMyShip()->SetShipDeathTimer(5);
				}
					
			}
			else
			{
				thisapp.GetMyTimebomb()->isDone = true;
			}			
		}
	}

	void ProcessReceivedPacket_NewMedkit(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession)
	{
		struct PKT_S2C_NewMedkit NewMedkit;
		ToProsessSession.PacketMessage >> NewMedkit;

		Medkit *medkit = new Medkit(NewMedkit.x, NewMedkit.y);
		thisapp.SetMyMedkit(medkit);
	}

	void ProcessReceivedPacket_MedkitTaken(Application &thisapp, struct HNet::_ProcessSession &ToProsessSession)
	{
		struct PKT_S2C_MedkitTaken MedkitTakenData;
		ToProsessSession.PacketMessage >> MedkitTakenData;

		// If i took the medkit
		if (thisapp.GetMyShip()->GetShipID() == MedkitTakenData.TakenShipID)
		{
			thisapp.GetMyShip()->SetShipHP(5);
			Medkit* myMedkit = thisapp.GetMyMedkit();
			delete myMedkit;
			thisapp.SetMyMedkit(NULL);
			return;
		}

		
		//if someone else took the medkit
		for (int i = 0; i < thisapp.GetEnemyShipList()->size(); ++i)
		{
			if (thisapp.GetEnemyShipList()->at(i)->GetShipID() == MedkitTakenData.TakenShipID)
			{
				Ship* enemyShip = thisapp.GetEnemyShipList()->at(i);
				enemyShip->SetShipHP(5);
				Medkit* myMedkit = thisapp.GetMyMedkit();
				delete myMedkit;
				thisapp.SetMyMedkit(NULL);
				break;
			}
		}
	}
}