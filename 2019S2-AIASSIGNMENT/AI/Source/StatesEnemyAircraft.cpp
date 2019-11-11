#include "StatesEnemyAircraft.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Moving
StateEMoving::StateEMoving(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateEMoving::~StateEMoving()
{
}

void StateEMoving::Enter()
{
	m_go->moveSpeed = 1;
}

void StateEMoving::Update(double dt)
{
	if (m_go->targetGO == NULL || m_go->targetGO->active == false || m_go->targetGO->sm->GetCurrentState() == "Destroyed")
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_HARVESTER_REPAIRBOT, 20 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
	}

	//Movement for going to harvester
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	if (m_go->targetGO)
	{
		float XDif = m_go->pos.x - m_go->targetGO->pos.x;
		if (XDif < 0)
			XDif = -XDif;

		float YDif = m_go->pos.y - m_go->targetGO->pos.y;
		if (YDif < 0)
			YDif = -YDif;

		if (XDif > YDif)
		{
			if (m_go->targetGO->pos.x > m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->targetGO->pos.y > m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}

		//Distance check for harvester
		//Set to attack if close enough
		if ((m_go->pos - m_go->targetGO->pos).Length() < 7 * SceneData::GetInstance()->getGridSize())
		{
			m_go->sm->SetNextState("Attack");
		}
	}
	else
	{
		//get out of the map if no more units
		m_go->moveDown = m_go->moveLeft = m_go->moveRight = false;
	}

	if (m_go->hp <= 0)
	{
		m_go->sm->SetNextState("Destroyed");
	}
}

void StateEMoving::Exit()
{
}

//State Attacking
StateEAttacking::StateEAttacking(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateEAttacking::~StateEAttacking()
{
}

void StateEAttacking::Enter()
{
	m_go->moveSpeed = 0;
	attackTimer = 0;
}

void StateEAttacking::Update(double dt)
{
	//Set back to moving state if target not found/dead or out of range
	if (!m_go->targetGO || m_go->targetGO->active == false || m_go->targetGO->sm->GetCurrentState() == "Destroyed")
	{
		m_go->sm->SetNextState("Moving");
	}
	else if ((m_go->pos - m_go->targetGO->pos).Length() > 10 * SceneData::GetInstance()->getGridSize())
	{
		m_go->sm->SetNextState("Moving");
	}

	//Attack every 0.5s
	attackTimer += (float)dt;
	if (attackTimer > 0.5f)
	{
		MessageSpawn *msg = new MessageSpawn(m_go, MessageSpawn::SPAWN_ENEMYBULLET);
		PostOffice::GetInstance()->Send("Scene", msg);
		attackTimer = 0;
	}

	if (m_go->hp <= 0)
	{
		m_go->sm->SetNextState("Destroyed");
	}
}

void StateEAttacking::Exit()
{
}

//State Destroyed
StateEDestroyed::StateEDestroyed(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateEDestroyed::~StateEDestroyed()
{
}

void StateEDestroyed::Enter()
{
	m_go->active = false;
}

void StateEDestroyed::Update(double dt)
{
		
}

void StateEDestroyed::Exit()
{
}