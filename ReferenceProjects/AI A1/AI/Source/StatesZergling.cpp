#include "StatesZergling.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Moving
StateZMoving::StateZMoving(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateZMoving::~StateZMoving()
{
}

void StateZMoving::Enter()
{
	m_go->moveSpeed = 1;
	timerEnemy = 0;
}

void StateZMoving::Update(double dt)
{
	//Move around randomly looking for a target
	m_go->moveLeft = m_go->moveRight = m_go->moveDown = m_go->moveUp = true;

	timerEnemy += (float)dt;

	//Check if enemy is nearby
	if (timerEnemy > 1)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_FRIENDLY_UNIT, 3 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
		timerEnemy = 0;
	}

	//if there is enemy nearby
	if (m_go->targetGO)
	{
		m_go->sm->SetNextState("Attack");
	}

	if (m_go->hp <= 0)
		m_go->sm->SetNextState("Destroyed");
}

void StateZMoving::Exit()
{
}

//State Attacking
StateZAttacking::StateZAttacking(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateZAttacking::~StateZAttacking()
{	
}

void StateZAttacking::Enter()
{
	m_go->moveSpeed = 1.5f;
	attackTimer = 0;
}

void StateZAttacking::Update(double dt)
{
	if (m_go->targetGO == NULL || m_go->targetGO->active == false || m_go->targetGO->sm->GetCurrentState() == "Destroyed")
	{
		m_go->targetGO = NULL;
		m_go->sm->SetNextState("Moving");
	}

	attackTimer += (float)dt;

	//Chase targetted enemy and continuously attack it
	if (m_go->targetGO)
	{
		m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
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

		if ((m_go->pos - m_go->targetGO->pos).Length() < SceneData::GetInstance()->getGridSize() && attackTimer > 0.5f)
		{
			m_go->targetGO->hp--;
			switch(m_go->targetGO->type)
			{
			case GameObject::GO_HARVESTER:
				m_go->targetGO->sm->SetNextState("Attacked");
				m_go->targetGO->targetGO = m_go;
				break;
			case GameObject::GO_REPAIRBOT:
				m_go->targetGO->sm->SetNextState("Attacked");
				m_go->targetGO->targetGO = m_go;
				break;
			case GameObject::GO_ARMOREDSOLDIER:
				m_go->targetGO->targetGO = m_go;
				break;
			}
			attackTimer = 0;
		}
	}

	if (m_go->hp <= 0)
		m_go->sm->SetNextState("Destroyed");
}

void StateZAttacking::Exit()
{
}

//State Destroyed
StateZDestroyed::StateZDestroyed(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateZDestroyed::~StateZDestroyed()
{
}

void StateZDestroyed::Enter()
{
	m_go->active = false;
}

void StateZDestroyed::Update(double dt)
{
}

void StateZDestroyed::Exit()
{
}