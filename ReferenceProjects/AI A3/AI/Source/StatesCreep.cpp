#include "StatesCreep.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Movement
StateCMovement::StateCMovement(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateCMovement::~StateCMovement()
{
}

void StateCMovement::Enter()
{
	m_go->moveSpeed = 1;
}

void StateCMovement::Update(double dt)
{
	Vector3 pos(m_go->pos.x, m_go->pos.y, 0);
	Vector3 target(m_go->target.x, m_go->target.y, 0);

	if ((pos - target).Length() < 1.f)
	{
		m_go->currentPathIndex++;
		if (m_go->currentPathIndex >= m_go->gPath.size())
		{
			MessageDamage *msg = new MessageDamage(m_go);
			PostOffice::GetInstance()->Send("SceneGraph", msg);
			m_go->active = false;
		}

		if (m_go->currentPathIndex < m_go->gPath.size())
		{
			m_go->target.x = m_go->gPath[m_go->currentPathIndex]->pos.x;
			m_go->target.y = m_go->gPath[m_go->currentPathIndex]->pos.y;
		}
	}

	if (m_go->hp <= 0)
		m_go->active = false;

	//Check if enemy is nearby
	MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_ENEMY, 5);
	PostOffice::GetInstance()->Send("SceneGraph", msg);

	//Set to attack if there is enemy nearby
	if (m_go->targetGO)
	{
		m_go->previousPathIndex = m_go->currentPathIndex;
		m_go->sm->SetNextState("Attack");
	}
}

void StateCMovement::Exit()
{
}

//State Attack
StateCAttack::StateCAttack(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateCAttack::~StateCAttack()
{
}

void StateCAttack::Enter()
{
	timerAttack = m_go->attackSpeed;
}

void StateCAttack::Update(double dt)
{
	if (m_go->targetGO == NULL || m_go->targetGO->active == false || m_go->targetGO->hp <= 0)
	{
		//Check if enemy is nearby
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_ENEMY, 5);
		PostOffice::GetInstance()->Send("SceneGraph", msg);
	}

	//Set to movement if there is no enemy nearby
	if (m_go->targetGO == NULL)
	{
		m_go->target.x = m_go->gPath[m_go->currentPathIndex]->pos.x;
		m_go->target.y = m_go->gPath[m_go->currentPathIndex]->pos.y;
		m_go->sm->SetNextState("Movement");
	}

	if (m_go->targetGO)
	{
		Vector3 cPos(m_go->pos.x, m_go->pos.y, 0);
		Vector3 tPos(m_go->targetGO->pos.x, m_go->targetGO->pos.y, 0);

		if (m_go->targetGO->active && (tPos - cPos).Length() > m_go->range)
		{
			m_go->moveSpeed = 1;
			m_go->target.x = m_go->targetGO->pos.x;
			m_go->target.y = m_go->targetGO->pos.y;

			//find closest waypoint
			float closestDist = 100000;
			int lowestIndex;
			for (int i = 0; i < m_go->gPath.size(); ++i)
			{
				if ((m_go->gPath[i]->pos - m_go->pos).Length() < closestDist)
				{
					lowestIndex = i;
					closestDist = (m_go->gPath[i]->pos - m_go->pos).Length();
				}					
			}

			if (m_go->currentPathIndex < lowestIndex && lowestIndex - m_go->previousPathIndex == 1)
				m_go->currentPathIndex = lowestIndex;
		}
		else
		{
			m_go->moveSpeed = 0;
			
			if (timerAttack <= 0)
			{
				m_go->targetGO->hp -= m_go->damage;
				timerAttack = m_go->attackSpeed;
			}
		}			
	}	

	timerAttack -= dt;
	
	if (m_go->hp <= 0)
		m_go->active = false;	
}

void StateCAttack::Exit()
{
}