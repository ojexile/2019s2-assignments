#include "StatesFishFood.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Grow
StateGrow::StateGrow(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateGrow::~StateGrow()
{
}

void StateGrow::Enter()
{
	m_go->moveSpeed = 0.5f;
	timer = 0;
}

void StateGrow::Update(double dt)
{
	timer += (float)dt;

	if (timer >= 15)
		m_go->sm->SetNextState("Evolve");
}

void StateGrow::Exit()
{
}

//State Evolve
StateEvolve::StateEvolve(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateEvolve::~StateEvolve()
{
}

void StateEvolve::Enter()
{
	MessageEvolve *msg = new MessageEvolve(m_go, MessageEvolve::EVOLVE);
	PostOffice::GetInstance()->Send("Scene", msg);
	m_go->active = false;
}

void StateEvolve::Update(double dt)
{
}

void StateEvolve::Exit()
{
}