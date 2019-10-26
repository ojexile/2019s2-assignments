#include "StatesShark.h"
#include "SceneData.h"
#include "ConcreteMessages.h"
#include "PostOffice.h"

//State crazy
StateCrazy::StateCrazy(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateCrazy::~StateCrazy()
{
}

void StateCrazy::Enter()
{
	m_go->moveSpeed = 2.5f;
	m_go->TargetFish = NULL;
}

void StateCrazy::Update(double dt)
{
	if (m_go->TargetFish)
	{
		if (m_go->TargetFish->sm->GetCurrentState() == "Dead")
			m_go->TargetFish = NULL;
	}

	if (m_go->TargetFish == NULL)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::HIGHEST_ENERGYFISH, 0);
		PostOffice::GetInstance()->Send("Scene", msg);
	}

	//Movement for chasing
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	if (m_go->TargetFish)
	{
		float XDif = m_go->pos.x - m_go->TargetFish->pos.x;
		if (XDif < 0)
			XDif = -XDif;

		float YDif = m_go->pos.y - m_go->TargetFish->pos.y;
		if (YDif < 0)
			YDif = -YDif;

		if (XDif > YDif)
		{
			if (m_go->TargetFish->pos.x > m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->TargetFish->pos.y > m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}
	}

	if (SceneData::GetInstance()->getFishCount() <= 10)
	{
		m_go->sm->SetNextState("Naughty");
	}
}

void StateCrazy::Exit()
{
}

//State naughty
StateNaughty::StateNaughty(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateNaughty::~StateNaughty()
{
}

void StateNaughty::Enter()
{
	m_go->moveSpeed = 2;
	m_go->TargetFish = NULL;
}

void StateNaughty::Update(double dt)
{
	if (m_go->TargetFish)
	{
		if (m_go->TargetFish->sm->GetCurrentState() == "Dead")
			m_go->TargetFish = NULL;
	}

	if (m_go->TargetFish == NULL)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_FULLFISH, 0);
		PostOffice::GetInstance()->Send("Scene", msg);
	}

	//Movement for chasing
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	if (m_go->TargetFish)
	{
		float XDif = m_go->pos.x - m_go->TargetFish->pos.x;
		if (XDif < 0)
			XDif = -XDif;

		float YDif = m_go->pos.y - m_go->TargetFish->pos.y;
		if (YDif < 0)
			YDif = -YDif;

		if (XDif > YDif)
		{
			if (m_go->TargetFish->pos.x > m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->TargetFish->pos.y > m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}
	}

	if (SceneData::GetInstance()->getFishCount() > 10)
	{
		m_go->sm->SetNextState("Crazy");
	}
	else if (SceneData::GetInstance()->getFishCount() <= 4)
	{
		m_go->sm->SetNextState("Happy");
	}
}

void StateNaughty::Exit()
{
}

//State happy
StateHappy::StateHappy(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
	m_go->moveSpeed = 1;
}

StateHappy::~StateHappy()
{
}

void StateHappy::Enter()
{
	m_go->moveSpeed = 0.75;
	MessageSpawn *msg = new MessageSpawn(m_go, MessageSpawn::SPAWN_FISH);
	PostOffice::GetInstance()->Send("Scene", msg);
}

void StateHappy::Update(double dt)
{
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	if (SceneData::GetInstance()->getFishCount() > 4)
	{
		m_go->sm->SetNextState("Naughty");
	}
}

void StateHappy::Exit()
{
}