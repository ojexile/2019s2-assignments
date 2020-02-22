#include "StatesRepairer.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Moving
StateRMoving::StateRMoving(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateRMoving::~StateRMoving()
{
}

void StateRMoving::Enter()
{
	m_go->moveSpeed = 0.8f;
}

void StateRMoving::Update(double dt)
{
	if (m_go->targetGO == NULL || m_go->targetGO->active == false || m_go->targetGO->sm->GetCurrentState() != "Destroyed")
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::RANDOM_DESTROYED_UNIT, 20 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
	}

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

		if ((m_go->pos - m_go->targetGO->pos).Length() < SceneData::GetInstance()->getGridSize())
		{
			m_go->sm->SetNextState("Repairing");
		}
	}
	//Go back to base
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

		if (m_go->pos.x < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize()
			&& m_go->pos.y < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize())
		{
			m_go->active = false;
		}
	}

	if (m_go->hp <= 0)
		m_go->sm->SetNextState("Destroyed");
}

void StateRMoving::Exit()
{
}

//State Repairing
StateRRepairing::StateRRepairing(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateRRepairing::~StateRRepairing()
{
}

void StateRRepairing::Enter()
{
	m_go->moveSpeed = 0;
}

void StateRRepairing::Update(double dt)
{
	m_go->targetGO->repairTime += (float)dt;

	if (m_go->targetGO->sm->GetCurrentState() != "Destroyed")
		m_go->sm->SetNextState("Moving");
}

void StateRRepairing::Exit()
{
}

//State Attacked
StateRAttacked::StateRAttacked(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateRAttacked::~StateRAttacked()
{
}

void StateRAttacked::Enter()
{
	m_go->moveSpeed = 2;
	runTimer = 0;
}

void StateRAttacked::Update(double dt)
{
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

		if (m_go->pos.x < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize()
			&& m_go->pos.y < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize())
		{
			m_go->active = false;
		}
	}

	runTimer += (float)dt;

	if (runTimer > 2.f)
	{
		m_go->sm->SetNextState("Moving");
	}

	if (m_go->hp <= 0)
		m_go->sm->SetNextState("Destroyed");
}

void StateRAttacked::Exit()
{
}

//State Destroyed
StateRDestroyed::StateRDestroyed(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateRDestroyed::~StateRDestroyed()
{
}

void StateRDestroyed::Enter()
{
	m_go->moveSpeed = 0;
	m_go->repairTime = 0;
}

void StateRDestroyed::Update(double dt)
{
	if (m_go->repairTime >= 4)
	{
		m_go->hp = 15;
		m_go->sm->SetNextState("Moving");		
	}
}

void StateRDestroyed::Exit()
{
}