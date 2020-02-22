#include "SceneMovement.h"
#include "SceneData.h"
//#include "StatesFish.h"
//#include "StatesShark.h"
//#include "StatesFishFood.h"
#include "GL\glew.h"
#include "Application.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"

#include "StatesPatroller.h"
#include "StatesEnemy.h"
#include "StatesHarvester.h"
#include "StatesRepairer.h"

#include <sstream>

SceneMovement::SceneMovement()
{
}

SceneMovement::~SceneMovement()
{
}

void SceneMovement::Init()
{
	SceneBase::Init();
	PostOffice::GetInstance()->Register("Scene", this);
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;
	
	Math::InitRNG();

	SceneData::GetInstance()->setHarvestedMineral(0);
	SceneData::GetInstance()->setObjectCount(0);
	SceneData::GetInstance()->setNoGrid(20);
	SceneData::GetInstance()->setMineralCount(0);
	SceneData::GetInstance()->setHarvesterCount(0);
	SceneData::GetInstance()->setGridSize(m_worldHeight / SceneData::GetInstance()->getNoGrid());
	m_hourOfTheDay = 0;

	timerHarvester = timerPatroller = timerEnemy = timerRepairer = 0;

	//Spawn 1 shark
	/*GameObject* go = FetchGO(GameObject::GO_SHARK);
	go->type = GameObject::GO_SHARK;
	go->moveSpeed = 2;
	go->scale.Set(SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize());
	go->pos.Set(SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 19) * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 19) * SceneData::GetInstance()->getGridSize(), 1);
	go->target = go->pos;
	go->sm->SetNextState("Happy");

	overfull = deathByHunger = deathByShark = 0;*/
}

bool SceneMovement::Handle(Message *msg)
{
	MessageWRU *messageWRU = dynamic_cast<MessageWRU*>(msg);
	if (messageWRU)
	{
		switch (messageWRU->type)
		{
		case MessageWRU::RANDOM_MINERAL:
		{
			int index = Math::RandIntMinMax(0, 4);

			for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *go = (GameObject *)*it;
				if (go->active == true && go->type == GameObject::GO_MINERAL)
				{
					if (index > 0)
					{
						index--;
					}
					else
					{
						messageWRU->go->targetMineral = go;
						break;
					}
				}
			}

			//if for some reason there is less than 5 minerals in the map, just assign to 1st mineral found
			if (index > 0)
			{
				for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					GameObject *go = (GameObject *)*it;
					if (go->active == true && go->type == GameObject::GO_MINERAL)
					{
						messageWRU->go->targetMineral = go;
						break;
					}
				}
			}
			break;
		}
		case MessageWRU::NEAREST_ENEMY:
		{
			int shortestDist = 1000;
			messageWRU->go->targetGO = NULL;
			for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *go = (GameObject *)*it;
				if (go->active && go->type == GameObject::GO_ENEMY)
				{
					if ((go->pos - messageWRU->go->pos).Length() < shortestDist && (go->pos - messageWRU->go->pos).Length() < messageWRU->threshold)
					{
						shortestDist = (int)(go->pos - messageWRU->go->pos).Length();
						messageWRU->go->targetGO = go;
					}
				}
			}
			break;
		}
		case MessageWRU::NEAREST_HARVESTER_REPAIRER:
		{
			int shortestDist = 1000;
			messageWRU->go->targetGO = NULL;
			for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *go = (GameObject *)*it;
				if (go->active && (go->type == GameObject::GO_HARVESTER || go->type == GameObject::GO_REPAIRER))
				{
					if (go->sm->GetCurrentState() == "Destroyed")
						continue;

					if ((go->pos - messageWRU->go->pos).Length() < shortestDist && (go->pos - messageWRU->go->pos).Length() < messageWRU->threshold)
					{
						shortestDist = (int)(go->pos - messageWRU->go->pos).Length();
						messageWRU->go->targetGO = go;
					}
				}
			}
			break;
		}
		case MessageWRU::NEAREST_FRIENDLY_UNIT:
		{
			int shortestDist = 1000;
			messageWRU->go->targetGO = NULL;
			for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *go = (GameObject *)*it;
				if (go->active && (go->type == GameObject::GO_HARVESTER || go->type == GameObject::GO_REPAIRER || go->type == GameObject::GO_PATROLLER))
				{
					if (go->sm->GetCurrentState() == "Destroyed")
						continue;

					if ((go->pos - messageWRU->go->pos).Length() < shortestDist && (go->pos - messageWRU->go->pos).Length() < messageWRU->threshold)
					{
						shortestDist = (int)(go->pos - messageWRU->go->pos).Length();
						messageWRU->go->targetGO = go;
					}
				}
			}
			break;
		}
		case MessageWRU::RANDOM_DESTROYED_UNIT:
		{
			messageWRU->go->targetGO = NULL;
			std::vector<int> indexes;

			for (int i = 0; i < m_goList.size(); ++i)
			{
				GameObject *go = m_goList[i];
				if (go->active && (go->type == GameObject::GO_HARVESTER || go->type == GameObject::GO_REPAIRER || go->type == GameObject::GO_PATROLLER))
				{
					if (go->sm->GetCurrentState() == "Destroyed")
					{
						indexes.push_back(i);
					}
				}
			}

			if (indexes.size() != 0)
			{
				int randomNum = Math::RandIntMinMax(0, indexes.size() - 1);
				messageWRU->go->targetGO = m_goList[indexes[randomNum]];
			}		
			break;
		}
		}
		delete msg;
		return true;
	}

	MessageSpawn *messageSpawn = dynamic_cast<MessageSpawn*>(msg);
	if (messageSpawn)
	{
		switch (messageSpawn->type)
		{
		case MessageSpawn::SPAWN_ENEMYBULLET:
		{
			GameObject* go = FetchGO(GameObject::GO_ENEMYBULLET);
			go->type = GameObject::GO_ENEMYBULLET;
			go->moveSpeed = 3;
			go->pos.Set(messageSpawn->go->pos.x, messageSpawn->go->pos.y, go->pos.z);
			go->scale = messageSpawn->go->scale;
			go->targetGO = messageSpawn->go->targetGO;
			go->target = go->pos;
			go->bulletOwner = messageSpawn->go;
			go->lifetime = 2;
			break;
		}
		case MessageSpawn::SPAWN_FRIENDLYBULLET:
		{
			GameObject* go = FetchGO(GameObject::GO_FRIENDLYBULLET);
			go->type = GameObject::GO_FRIENDLYBULLET;
			go->moveSpeed = 3;
			go->pos.Set(messageSpawn->go->pos.x, messageSpawn->go->pos.y, go->pos.z);
			go->scale = messageSpawn->go->scale;
			go->targetGO = messageSpawn->go->targetGO;
			go->target = go->pos;
			go->bulletOwner = messageSpawn->go;
			go->lifetime = 2;
			break;
		}
		}
		delete msg;
		return true;
	}

	delete msg;
	return false;
}

GameObject* SceneMovement::FetchGO(GameObject::GAMEOBJECT_TYPE type)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active && type == go->type)
		{
			go->active = true;
			go->pos.Set(0, 0, distance(m_goList.begin(), it) * 0.0001f);
			return go;
		}
	}

	for (unsigned i = 0; i < 5; ++i)
	{
		GameObject *go = new GameObject(type);
		m_goList.push_back(go);

		switch (go->type)
		{
		case GameObject::GO_PATROLLER:
			go->sm = new StateMachine();
			go->sm->AddState(new StatePatrollerPatrolling("Patrol", go));
			go->sm->AddState(new StatePatrollerAttacking("Attack", go));
			go->sm->AddState(new StatePatrollerDestroyed("Destroyed", go));
			break;
		case GameObject::GO_HARVESTER:
			go->sm = new StateMachine();
			go->sm->AddState(new StateHMoving("Moving", go));
			go->sm->AddState(new StateHHarvesting("Harvesting", go));
			go->sm->AddState(new StateHAttacked("Attacked", go));
			go->sm->AddState(new StateHDestroyed("Destroyed", go));
			break;
		case GameObject::GO_REPAIRER:
			go->sm = new StateMachine();
			go->sm->AddState(new StateRMoving("Moving", go));
			go->sm->AddState(new StateRRepairing("Repairing", go));
			go->sm->AddState(new StateRAttacked("Attacked", go));
			go->sm->AddState(new StateRDestroyed("Destroyed", go));
			break;
		case GameObject::GO_ENEMY:
			go->sm = new StateMachine();
			go->sm->AddState(new StateEMoving("Moving", go));
			go->sm->AddState(new StateEAttacking("Attack", go));
			go->sm->AddState(new StateEDestroyed("Destroyed", go));
			break;

		}
	}

	return FetchGO(type);
}

void SceneMovement::Update(double dt)
{
	SceneBase::Update(dt);

	static const float BALL_SPEED = 20.f;
	static const float HOUR_SPEED = 1.f;

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	
	if(Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if(Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}

	m_hourOfTheDay += HOUR_SPEED * static_cast<float>(dt) * m_speed;
	if (m_hourOfTheDay >= 24.f)
		m_hourOfTheDay = 0;

	//Input Section
	static bool bLButtonState = false;
	if(!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if(bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if(!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if(bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

	timerEnemy += (float)dt * m_speed;
	timerRepairer += (float)dt * m_speed;
	timerHarvester += (float)dt * m_speed;
	timerPatroller += (float)dt * m_speed;

	//Spawn Repairer
	if (destroyedCount > 0 && timerRepairer > 1.f && repairerCount < 8 && enemyCount <= 2)
	{
		GameObject *go = FetchGO(go->GO_REPAIRER);
		go->scale.Set(SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize());

		float posX, posY;
		int SpawnUp = Math::RandIntMinMax(0, 1);
		if (SpawnUp == 0)
		{
			posX = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 6) * SceneData::GetInstance()->getGridSize();
			posY = SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize();
		}
		else
		{
			posX = SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize();
			posY = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 6) * SceneData::GetInstance()->getGridSize();
		}

		go->pos.Set(posX, posY, go->pos.z);
		go->target = go->pos;
		go->type = GameObject::GO_REPAIRER;
		go->sm->SetNextState("Moving");
		go->hp = 15;

		timerRepairer = 0;
	}

	//Spawn Enemy
	if (timerEnemy > 8 && enemyCount <= 5)
	{
		int randCount = Math::RandIntMinMax(2, 4);

		for (int i = 0; i < randCount; ++i)
		{
			GameObject *go = FetchGO(go->GO_ENEMY);
			go->scale.Set(SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize());

			float posX, posY;
			int SpawnDir = Math::RandIntMinMax(0, 3);
			switch (SpawnDir)
			{
				//Left
			case 0:
				posX = SceneData::GetInstance()->getGridOffset() + 0 * SceneData::GetInstance()->getGridSize();
				posY = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(10, 19) * SceneData::GetInstance()->getGridSize();
				break;
				//Up
			case 1:
				posX = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(1, 19) * SceneData::GetInstance()->getGridSize();
				posY = SceneData::GetInstance()->getGridOffset() + 19 * SceneData::GetInstance()->getGridSize();
				break;
				//Right
			case 2:
				posX = SceneData::GetInstance()->getGridOffset() + 19 * SceneData::GetInstance()->getGridSize();
				posY = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(1, 19) * SceneData::GetInstance()->getGridSize();
				break;
				//Down
			case 3:
				posX = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(10, 19) * SceneData::GetInstance()->getGridSize();
				posY = SceneData::GetInstance()->getGridOffset() + 0 * SceneData::GetInstance()->getGridSize();
				break;
			}

			go->hp = 5;
			go->pos.Set(posX, posY, go->pos.z);
			go->target = go->pos;
			go->type = GameObject::GO_ENEMY;
			go->targetGO = NULL;
			go->sm->SetNextState("Moving");
		}
		timerEnemy = 0;
	}

	//Spawn Harvester
	if (timerHarvester > 1 && SceneData::GetInstance()->getHarvesterCount() < 10)
	{
		GameObject *go = FetchGO(go->GO_HARVESTER);
		go->scale.Set(SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize());

		float posX, posY;
		int SpawnUp = Math::RandIntMinMax(0, 1);
		if (SpawnUp == 0)
		{
			posX = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 6) * SceneData::GetInstance()->getGridSize();
			posY = SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize();
		}
		else
		{
			posX = SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize();
			posY = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 6) * SceneData::GetInstance()->getGridSize();
		}

		go->pos.Set(posX, posY, go->pos.z);
		go->target = go->pos;
		go->hp = 5;
		go->targetGO = NULL;
		go->type = GameObject::GO_HARVESTER;
		go->sm->SetNextState("Moving");
		go->carryingMineral = false;
		timerHarvester = 0;
	}

	//Spawn Patroller
	if (timerPatroller > 1.2f)
	{
		GameObject *go = FetchGO(go->GO_PATROLLER);
		go->scale.Set(SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize());
		go->pos.Set(SceneData::GetInstance()->getGridOffset() + 6 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 1);
		go->target = go->pos;
		go->type = GameObject::GO_PATROLLER;
		go->sm->SetNextState("Patrol");
		go->hp = 20;
		go->patrolCheckpointIndex = -1;
		timerPatroller = 0;
		go->targetGO = NULL;
	}

	//Kill all
	static bool bVState = false;
	if (!bVState && Application::IsKeyPressed('V'))
	{
		bVState = true;
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *go = (GameObject *)*it;

			MessageSendAll *msgAll = new MessageSendAll(go, MessageSendAll::KILL_ALL, 0);
			go->Handle(msgAll);
		}
	}
	else if (bVState && !Application::IsKeyPressed('V'))
	{
		bVState = false;
	}

	if (m_goList.capacity() < m_goList.size() + 100)
	{
		m_goList.reserve(m_goList.capacity() + 200);
	}

	//Spawn mineral
	if (SceneData::GetInstance()->getMineralCount() < 5)
	{
		bool canSpawn;
		float posX, posY;

		//check if in another mineral
		while (true)
		{
			canSpawn = true;
			int SpawnUp = Math::RandIntMinMax(0, 1);
			if (SpawnUp == 0)
			{
				posX = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 19) * SceneData::GetInstance()->getGridSize();
				posY = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(9, 19) * SceneData::GetInstance()->getGridSize();
			}
			else
			{
				posX = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(9, 19) * SceneData::GetInstance()->getGridSize();
				posY = SceneData::GetInstance()->getGridOffset() + Math::RandIntMinMax(0, 19) * SceneData::GetInstance()->getGridSize();
			}

			//check if same position as another mineral
			for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *go = (GameObject *)*it;

				if (go->type == GameObject::GO_MINERAL)
				{
					if (posX == go->pos.x && posY == go->pos.y)
					{
						canSpawn = false;
					}
				}
			}

			if (canSpawn == true)
				break;
		}
		
		GameObject* go = FetchGO(GameObject::GO_MINERAL); 
		go->type = GameObject::GO_MINERAL;
		go->moveSpeed = 0;
		go->scale.Set(SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridSize());
		go->pos.Set(posX, posY, 0);
		go->hp = 5;
		
		SceneData::GetInstance()->setMineralCount(SceneData::GetInstance()->getMineralCount() + 1);	
	}

	//Update GameObjects
	enemyCount = 0;
	enemyCount = 0;
	destroyedCount = 0;
	repairerCount = 0;
	int harvesterCount = 0;
	int objectCount = 0;
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;

		MessageSendAll *msgAll = new MessageSendAll(go, MessageSendAll::CHECK_ACTIVE, 0);
		if (go->Handle(msgAll))
		{
			objectCount++;
		}

		if (go->active == true && go->type != GameObject::GO_MINERAL && go->type != GameObject::GO_ENEMYBULLET && go->type != GameObject::GO_FRIENDLYBULLET)
		{
			go->Update(dt * m_speed);

			if ((go->type == GameObject::GO_PATROLLER || go->type == GameObject::GO_HARVESTER || go->type == GameObject::GO_REPAIRER) && go->sm->GetCurrentState() == "Destroyed")
				destroyedCount++;

			if (go->type == GameObject::GO_ENEMY)
				enemyCount++;

			else if (go->type == GameObject::GO_HARVESTER)
				harvesterCount++;
			else if (go->type == GameObject::GO_REPAIRER)
				repairerCount++;
		}
		else if (go->active == true && go->type == GameObject::GO_MINERAL)
		{
			if (go->hp == 0)
			{
				go->active = false;
				SceneData::GetInstance()->setMineralCount(SceneData::GetInstance()->getMineralCount() - 1);
			}
		}
		else if (go->active == true && (go->type == GameObject::GO_ENEMYBULLET || go->type == GameObject::GO_FRIENDLYBULLET))
		{
			//bullet to go to position
			go->moveLeft = go->moveRight = go->moveUp = go->moveDown = true;
			float XDif = go->pos.x - go->targetGO->pos.x;
			if (XDif < 0)
				XDif = -XDif;

			float YDif = go->pos.y - go->targetGO->pos.y;
			if (YDif < 0)
				YDif = -YDif;

			if (XDif > YDif)
			{
				if (go->targetGO->pos.x > go->pos.x)
					go->moveLeft = false;
				else
					go->moveRight = false;

				go->moveUp = go->moveDown = false;
			}
			else
			{
				if (go->targetGO->pos.y > go->pos.y)
					go->moveDown = false;
				else
					go->moveUp = false;

				go->moveLeft = go->moveRight = false;
			}
			
			go->lifetime -= (float)dt * m_speed;

			//if bullet lifetime ends despawn it
			if (go->lifetime <= 0)
			{
				go->active = false;
			}

			//if target is dead, despawn bullet when it reaches target location
			if (go->targetGO->sm->GetCurrentState() == "Destroyed")
			{
				if ((go->pos - go->targetGO->pos).Length() < SceneData::GetInstance()->getGridOffset())
				{
					go->active = false;
				}
			}
		}
	}

	SceneData::GetInstance()->setHarvesterCount(harvesterCount);
	SceneData::GetInstance()->setObjectCount(objectCount);

	//Collision check and response
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
			continue;
		if (go->type == GameObject::GO_MINERAL)
			continue;

		for (std::vector<GameObject *>::iterator it2 = it + 1; it2 != m_goList.end(); ++it2)
		{
			GameObject *go2 = static_cast<GameObject *>(*it2);
			if (!go2->active)
				continue;
			if (go2->type == GameObject::GO_MINERAL)
				continue;
			if (((go->type != GameObject::GO_ENEMYBULLET && go2->type != GameObject::GO_ENEMYBULLET) &&
				(go->type != GameObject::GO_FRIENDLYBULLET && go2->type != GameObject::GO_FRIENDLYBULLET)) ||
				go->type == GameObject::GO_ENEMYBULLET && go2->type == GameObject::GO_FRIENDLYBULLET ||
				go->type == GameObject::GO_FRIENDLYBULLET && go2->type == GameObject::GO_ENEMYBULLET ||
				go->type == go2->type)
				continue;

			float dist = (go->pos - go2->pos).Length();

			if (dist < SceneData::GetInstance()->getGridSize())
			{
				GameObject* goA = go;
				GameObject* goB = go2;

				//Make goA always bullet and goB always units
				if (go2->type == GameObject::GO_ENEMYBULLET ||
					go2->type == GameObject::GO_FRIENDLYBULLET)
				{
					goA = go2;
					goB = go;
				}

				if (goB->sm->GetCurrentState() != "Destroyed")
				{
					switch (goA->type)
					{
					case GameObject::GO_ENEMYBULLET:
						if (goB->type != GameObject::GO_ENEMY)
						{
							goA->active = false;
							goB->hp -= 1;
							
							switch (goB->type)
							{
							case GameObject::GO_HARVESTER:
								goB->targetGO = goA->bulletOwner;
								goB->sm->SetNextState("Attacked");
								break;
							case GameObject::GO_REPAIRER:
								goB->sm->SetNextState("Attacked");
								goB->targetGO = goA->bulletOwner;
								break;
							case GameObject::GO_PATROLLER:
								if (!(goB->targetGO))
								{
									goB->targetGO = goA->bulletOwner;
								}
								break;
							}
						}						
						break;
					case GameObject::GO_FRIENDLYBULLET:
						if (goB->type == GameObject::GO_ENEMY)
						{
							goA->active = false;
							goB->hp -= 1;
							
							//switch target priority to guards
							if(!(goB->targetGO) || goB->targetGO->type != GameObject::GO_PATROLLER)
								goB->targetGO = goA->bulletOwner;
						}	
					break;
					}					
				}
			}		
		}
	}

	//Movement Section
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			//if (go->steps > 100)
			//	continue;

			Vector3 dir = go->target - go->pos;
			if (dir.Length() < BALL_SPEED * dt * m_speed)
			{
				//GO->pos reach target
				go->pos = go->target;
				if (go->moveDown == go->moveLeft && go->moveLeft == go->moveUp && go->moveUp == go->moveRight)
				{
					float random = Math::RandFloatMinMax(0.f, 1.f);
					//Exercise: use probability to decide direction to go
					//Up
					if (random < 0.25f)
					{
						go->target.Set(go->pos.x, go->pos.y + SceneData::GetInstance()->getGridSize(), go->pos.z);
					}
					//Right
					else if (random < 0.5f)
					{
						go->target.Set(go->pos.x + SceneData::GetInstance()->getGridSize(), go->pos.y, go->pos.z);
					}
					//Down
					else if (random < 0.75f)
					{
						go->target.Set(go->pos.x, go->pos.y - SceneData::GetInstance()->getGridSize(), go->pos.z);
					}
					//Left
					else
					{
						go->target.Set(go->pos.x - SceneData::GetInstance()->getGridSize(), go->pos.y, go->pos.z);
					}
				}
				else
				{
					//Up
					if (go->moveUp)
					{
						go->target.Set(go->pos.x, go->pos.y + SceneData::GetInstance()->getGridSize(), go->pos.z);
					}
					//Right
					else if (go->moveRight)
					{
						go->target.Set(go->pos.x + SceneData::GetInstance()->getGridSize(), go->pos.y, go->pos.z);
					}
					//Down
					else if (go->moveDown)
					{
						go->target.Set(go->pos.x, go->pos.y - SceneData::GetInstance()->getGridSize(), go->pos.z);
					}
					//Left
					else if (go->moveLeft)
					{
						go->target.Set(go->pos.x - SceneData::GetInstance()->getGridSize(), go->pos.y, go->pos.z);
					}
				}

				//Boundaries for friendly units
				if (go->type != GameObject::GO_ENEMY)
				{
					if (go->target.x < 0 || go->target.x > SceneData::GetInstance()->getNoGrid() * SceneData::GetInstance()->getGridSize() || go->target.y < 0 || go->target.y > SceneData::GetInstance()->getNoGrid() * SceneData::GetInstance()->getGridSize())
						go->target = go->pos;
				}			

				if (go->pos.x < 0 || go->pos.x > SceneData::GetInstance()->getNoGrid() * SceneData::GetInstance()->getGridSize() || go->pos.y < 0 || go->pos.y > SceneData::GetInstance()->getNoGrid() * SceneData::GetInstance()->getGridSize())
					go->active = false;
			}
			else
			{
				dir.Normalize();
				go->pos += dir * BALL_SPEED * static_cast<float>(dt) * m_speed * go->moveSpeed;
			}
		}
	}
}

void SceneMovement::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);

		std::ostringstream ss;
		ss << go->id;
		RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0));
		modelStack.PopMatrix();
		break;
	}
	case GameObject::GO_MINERAL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		RenderMesh(meshList[GEO_MINERAL], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_HARVESTER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		if (go->sm->GetCurrentState() == "Moving")
		{
			RenderMesh(meshList[GEO_HARVESTER_MOVING], false);
		}
		else if (go->sm->GetCurrentState() == "Harvesting")
		{
			RenderMesh(meshList[GEO_HARVESTER_HARVESTING], false);
		}
		else if (go->sm->GetCurrentState() == "Attacked")
		{
			RenderMesh(meshList[GEO_HARVESTER_ATTACKED], false);
		}
		else if (go->sm->GetCurrentState() == "Destroyed")
		{
			RenderMesh(meshList[GEO_HARVESTER_DESTROYED], false);
		}
		modelStack.PopMatrix();

		if (go->carryingMineral == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y + 5, go->pos.z);
			modelStack.Scale(go->scale.x * 0.6f, go->scale.y * 0.6f, go->scale.z + 10);
			RenderMesh(meshList[GEO_MINERAL], false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_PATROLLER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		if (go->hp <= 10 && go->hp > 0)
		{
			RenderMesh(meshList[GEO_PATROLLER_DAMAGED], false);
		}
		else if (go->sm->GetCurrentState() == "Patrol")
		{
			RenderMesh(meshList[GEO_PATROLLER_PATROL], false);
		}
		else if (go->sm->GetCurrentState() == "Attack")
		{
			RenderMesh(meshList[GEO_PATROLLER_ATTACKING], false);
		}	
		else if (go->sm->GetCurrentState() == "Destroyed")
		{
			RenderMesh(meshList[GEO_PATROLLER_DESTROYED], false);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_REPAIRER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		if (go->sm->GetCurrentState() == "Moving")
		{
			RenderMesh(meshList[GEO_REPAIRER_MOVING], false);
		}
		else if (go->sm->GetCurrentState() == "Repairing")
		{
			RenderMesh(meshList[GEO_REPAIRER_REPAIRING], false);
		}
		else if (go->sm->GetCurrentState() == "Attacked")
		{
			RenderMesh(meshList[GEO_REPAIRER_ATTACKED], false);
		}
		else if (go->sm->GetCurrentState() == "Destroyed")
		{
			RenderMesh(meshList[GEO_REPAIRER_DESTROYED], false);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_ENEMY:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		RenderMesh(meshList[GEO_ENEMY], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_FRIENDLYBULLET:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		RenderMesh(meshList[GEO_FRIENDLYBULLET], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_ENEMYBULLET:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, 1);
		RenderMesh(meshList[GEO_ENEMYBULLET], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneMovement::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight * 0.5f, m_worldHeight * 0.5f, -1.f);
	modelStack.Scale(m_worldHeight, m_worldHeight, m_worldHeight);
	RenderMesh(meshList[GEO_BG], false);
	modelStack.PopMatrix();

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	//On screen text

	std::ostringstream ss;
	ss.precision(3);
	ss << "Speed:" << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 6);
	
	ss.str("");
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 3);

	ss.str("");
	ss << "Count:" << SceneData::GetInstance()->getObjectCount();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 9);

	//Xtra Stats
	ss.str("");
	ss << "Harvested Mineral Count:" << SceneData::GetInstance()->getHarvestedMineral();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 15);

	ss.str("");
	ss << "Harvester Count:" << SceneData::GetInstance()->getHarvesterCount();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 18);
	
	ss.str("");
	ss << "Total Enemy Count:" << enemyCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 21);

	ss.str("");
	ss << "Destroyed Units Count:" << destroyedCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 52, 24);

	RenderTextOnScreen(meshList[GEO_TEXT], "Movement", Color(0, 1, 0), 3, 52, 0);
}

void SceneMovement::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();		
		delete go;
		m_goList.pop_back();
	}
	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}