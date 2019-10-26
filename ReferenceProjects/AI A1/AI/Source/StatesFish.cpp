#include "StatesFish.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State too full
StateTooFull::StateTooFull(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateTooFull::~StateTooFull()
{
}

void StateTooFull::Enter()
{
	m_go->moveSpeed = 0;
}

void StateTooFull::Update(double dt)
{
	m_go->energy -= (float)dt;
	if (m_go->energy < 10)
	{
		m_go->sm->SetNextState("Full");
	}
}

void StateTooFull::Exit()
{
}

//State Full
StateFull::StateFull(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateFull::~StateFull()
{
}

void StateFull::Enter()
{
	m_go->moveSpeed = 0.75f;
	m_go->targetGO = NULL;
	timer = 0;
}

void StateFull::Update(double dt)
{
	if (timer > 1)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_SHARK, 5 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
		timer = 0;
	}
	
	timer += (float)dt;
	m_go->energy -= (float)dt;
	
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

	if (m_go->energy >= 10)
	{
		m_go->sm->SetNextState("TooFull");
		//overfull++;
	}
	else if (m_go->energy < 5)
	{
		m_go->sm->SetNextState("Hungry");
	}
}

void StateFull::Exit()
{
}

//State Hungry
StateHungry::StateHungry(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateHungry::~StateHungry()
{
}

void StateHungry::Enter()
{
	m_go->moveSpeed = 0.5f;
	m_go->targetGO = NULL;

	MessageSpawn *msg = new MessageSpawn(m_go, MessageSpawn::SPAWN_FOOD);
	PostOffice::GetInstance()->Send("Scene", msg);
}

void StateHungry::Update(double dt)
{
	if (m_go->targetGO == NULL || m_go->targetGO->active == false)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_FISHFOOD, 10 * SceneData::GetInstance()->getGridSize());
		if(PostOffice::GetInstance()->Send("Scene", msg))
		{
			MessageStop *msg = new MessageStop(MessageStop::STOP_MOVING);
			m_go->targetGO->Handle(msg);
		}
	}

	//Movement for chasing
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
	}

	m_go->energy -= (float)dt;
	if (m_go->energy >= 5)
	{
		m_go->sm->SetNextState("Full");
	}
	else if (m_go->energy <= 0)
	{
		if (m_go->energy > -1)
		{
			//deathByHunger++;
		}
		m_go->sm->SetNextState("Dead");
	}
}

void StateHungry::Exit()
{
}

//State Dead
StateDead::StateDead(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateDead::~StateDead()
{
}

void StateDead::Enter()
{
	m_go->countDown = 3;
	m_go->moveSpeed = 0;
}

void StateDead::Update(double dt)
{
	m_go->countDown -= (float)dt;

	if (m_go->countDown <= 0)
	{
		m_go->active = false;
		//m_objectCount--;
	}
}

void StateDead::Exit()
{
}