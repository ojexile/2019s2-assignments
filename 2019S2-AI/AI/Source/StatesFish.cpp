#include "StatesFish.h"

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
	//overfull++
	m_go->moveSpeed = 0;
}

void StateTooFull::Update(double dt)
{
	m_go->energy -= dt;
	if (m_go->energy < 10)
	{
		m_go->sm->SetNextState("StateFull");
	}
}

void StateTooFull::Exit()
{
}

///============================================================

StateFull::StateFull(const std::string& stateID, GameObject* go)
	: State(stateID),
	m_go(go)
{
}

StateFull::~StateFull()
{
}

void StateFull::Enter()
{
	m_go->moveSpeed = 2;
}

void StateFull::Update(double dt)
{
	m_go->energy -= dt;
	
	if (m_go->energy < 5)
	{
		m_go->sm->SetNextState("StateHungry");
	}
	else if (m_go->energy >= 10)
	{
		m_go->sm->SetNextState("StateTooFull");
	}
}

void StateFull::Exit()
{
}

///============================================================

StateHungry::StateHungry(const std::string& stateID, GameObject* go)
	: State(stateID),
	m_go(go)
{
}

StateHungry::~StateHungry()
{
}

void StateHungry::Enter()
{
	m_go->moveSpeed = 1;
}

void StateHungry::Update(double dt)
{
	m_go->energy -= dt;

	if (m_go->energy >= 5)
	{
		m_go->sm->SetNextState("StateFull");
	}
	else if (m_go->energy <= 0)
	{
		if (m_go->energy > -1)
		{
			// deathByHunger++
		}
		m_go->sm->SetNextState("StateDead");
	}
}

void StateHungry::Exit()
{
}

///============================================================

StateDead::StateDead(const std::string& stateID, GameObject* go)
	: State(stateID),
	m_go(go) 
{
}

StateDead::~StateDead()
{
}

void StateDead::Enter()
{
	m_despawnTimer = 3.f;
	m_go->moveSpeed = 0;
}

void StateDead::Update(double dt)
{
	m_despawnTimer -= dt;

	if (m_despawnTimer <= 0)
	{
		m_go->active = false;
	}
}

void StateDead::Exit()
{

}

