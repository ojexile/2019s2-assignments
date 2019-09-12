#include "StatesHarvester.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Moving
StateHMoving::StateHMoving(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateHMoving::~StateHMoving()
{
}

void StateHMoving::Enter()
{
	m_go->moveSpeed = 0.4f;
	m_go->targetMineral = NULL;
	timerEnemy = 0;
}

void StateHMoving::Update(double dt)
{
	if (m_go->carryingMineral == false)
	{
		//Get mineral target to harvest
		if (m_go->targetMineral == NULL || m_go->targetMineral->active == false)
		{
			MessageWRU *msg = new MessageWRU(m_go, MessageWRU::RANDOM_MINERAL, 20 * SceneData::GetInstance()->getGridSize());
			PostOffice::GetInstance()->Send("Scene", msg);
		}

		//Movement for going to mineral
		m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
		float XDif = m_go->pos.x - m_go->targetMineral->pos.x;
		if (XDif < 0)
			XDif = -XDif;

		float YDif = m_go->pos.y - m_go->targetMineral->pos.y;
		if (YDif < 0)
			YDif = -YDif;

		if (XDif > YDif)
		{
			if (m_go->targetMineral->pos.x > m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->targetMineral->pos.y > m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}

		//Distance check for mineral
		if ((m_go->pos - m_go->targetMineral->pos).Length() < SceneData::GetInstance()->getGridSize())
		{
			m_go->sm->SetNextState("Harvesting");
		}
	}

	//Going back to base with mineral
	else
	{
		//Set base location
		m_go->targetPos = Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 1);

		//Movement for going back
		m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
		float XDif = m_go->pos.x - m_go->targetPos.x;
		if (XDif < 0)
			XDif = -XDif;

		float YDif = m_go->pos.y - m_go->targetPos.y;
		if (YDif < 0)
			YDif = -YDif;

		if (XDif > YDif)
		{
			if (m_go->targetPos.x > m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->targetPos.y > m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}
	}

	//Collect mineral when reach base
	if (m_go->pos.x < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize()
		&& m_go->pos.y < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize())
	{
		if (m_go->carryingMineral)
		{
			SceneData::GetInstance()->setHarvestedMineral(SceneData::GetInstance()->getHarvestedMineral() + 1);
			m_go->carryingMineral = false;
		}			
	}

	timerEnemy += (float)dt;

	//Check if enemy is nearby
	if (timerEnemy > 1)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_ENEMY, 3 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
		timerEnemy = 0;
	}

	//if there is enemy nearby
	if (m_go->targetGO)
	{
		m_go->sm->SetNextState("Attacked");
	}

	//check if destroyed
	if (m_go->hp <= 0)
	{
		m_go->sm->SetNextState("Destroyed");
	}
}

void StateHMoving::Exit()
{
}

//State Harvesting
StateHHarvesting::StateHHarvesting(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateHHarvesting::~StateHHarvesting()
{
}

void StateHHarvesting::Enter()
{
	m_go->moveSpeed = 0;
	timerEnemy = 0;
	timerHarvest = 0;
}

void StateHHarvesting::Update(double dt)
{
	//Check if mineral still has hp
	if (!(m_go->targetMineral) || m_go->targetMineral->active == false || m_go->targetMineral->type != GameObject::GO_MINERAL)
	{
		m_go->sm->SetNextState("Moving");
	}

	timerHarvest += (float)dt;

	//if harvest finish
	if (timerHarvest > 4)
	{
		m_go->targetMineral->hp--;
		m_go->carryingMineral = true;
		m_go->sm->SetNextState("Moving");
	}

	timerEnemy += (float)dt;

	//Check if enemy is nearby
	if (timerEnemy > 1)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_ENEMY, 3 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
		timerEnemy = 0;
	}

	//if there is enemy nearby
	if (m_go->targetGO)
	{
		m_go->sm->SetNextState("Attacked");
	}

	if (m_go->hp <= 0)
	{
		m_go->sm->SetNextState("Destroyed");
	}
}

void StateHHarvesting::Exit()
{
}

//State Attacked
StateHAttacked::StateHAttacked(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateHAttacked::~StateHAttacked()
{
}

void StateHAttacked::Enter()
{
	m_go->moveSpeed = 0.7f;
	timerEnemy = 0;
}

void StateHAttacked::Update(double dt)
{
	timerEnemy += (float)dt;

	//Check if enemy is nearby
	if (timerEnemy > 1)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_ENEMY, 3 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
		timerEnemy = 0;
	}

	if (!(m_go->targetGO))
	{
		m_go->sm->SetNextState("Moving");
	}

	//Movement for running
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	if (m_go->targetGO)
	{
		float XDif = m_go->pos.x - m_go->targetGO->pos.x;
		if (XDif < 0)
			XDif = -XDif;

		float YDif = m_go->pos.y - m_go->targetGO->pos.y;
		if (YDif < 0)
			YDif = -YDif;

		if (XDif < YDif)
		{
			if (m_go->targetGO->pos.x < m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->targetGO->pos.y < m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}
	}	

	//Hide if reach base
	if (m_go->pos.x < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize()
		&& m_go->pos.y < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize())
	{
		m_go->active = false;

		if(m_go->carryingMineral)
			SceneData::GetInstance()->setHarvestedMineral(SceneData::GetInstance()->getHarvestedMineral() + 1);
	}

	if (m_go->hp <= 0)
	{
		m_go->sm->SetNextState("Destroyed");
	}
}

void StateHAttacked::Exit()
{
}

//State Destroyed
StateHDestroyed::StateHDestroyed(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateHDestroyed::~StateHDestroyed()
{
}

void StateHDestroyed::Enter()
{
	m_go->moveSpeed = 0;
	m_go->repairTime = 0;
}

void StateHDestroyed::Update(double dt)
{
	if (m_go->repairTime >= 2)
	{
		m_go->hp = 5;
		m_go->sm->SetNextState("Moving");	
	}
}

void StateHDestroyed::Exit()
{
}