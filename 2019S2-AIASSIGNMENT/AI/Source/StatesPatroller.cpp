#include "StatesPatroller.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"

//State Patrolling
StatePatrollerPatrolling::StatePatrollerPatrolling(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StatePatrollerPatrolling::~StatePatrollerPatrolling()
{
}

void StatePatrollerPatrolling::Enter()
{
	m_go->moveSpeed = 1;
	timerEnemy = 0;

	if (m_go->patrolCheckpointIndex == -1)
	{
		int randomPatrol = Math::RandIntMinMax(0, 2);

		switch (randomPatrol)
		{
		case 0:
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 8 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 8 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 8 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 8 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 0));
			break;
		case 1:
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 13 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 13 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 13 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 13 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 0));
			break;
		case 2:
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 17 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 17 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 17 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 17 * SceneData::GetInstance()->getGridSize(), 0));
			m_go->PatrolCheckpoints.push_back(Vector3(SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + 2 * SceneData::GetInstance()->getGridSize(), 0));
			break;
		}

		m_go->patrolCheckpointIndex = 0;
	}
	
}

void StatePatrollerPatrolling::Update(double dt)
{
	if (m_go->patrolCheckpointIndex == -1)
		m_go->patrolCheckpointIndex = 0;

	//Movement to get to position
	m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
	float xDiff = m_go->pos.x - m_go->PatrolCheckpoints[m_go->patrolCheckpointIndex].x;
	if (xDiff < 0)
		xDiff = -xDiff;

	float yDiff = m_go->pos.y - m_go->PatrolCheckpoints[m_go->patrolCheckpointIndex].y;
	if (yDiff < 0)
		yDiff = -yDiff;

	if (xDiff > yDiff)
	{
		if (m_go->PatrolCheckpoints[m_go->patrolCheckpointIndex].x > m_go->pos.x)
			m_go->moveLeft = false;
		else
			m_go->moveRight = false;

		m_go->moveUp = m_go->moveDown = false;
	}
	else
	{
		if (m_go->PatrolCheckpoints[m_go->patrolCheckpointIndex].y > m_go->pos.y)
			m_go->moveDown = false;
		else
			m_go->moveUp = false;

		m_go->moveLeft = m_go->moveRight = false;
	}

	//Check if reached base
	if (m_go->patrolCheckpointIndex == m_go->PatrolCheckpoints.size() - 1)
	{
		if (m_go->pos.x < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize()
			&& m_go->pos.y < SceneData::GetInstance()->getGridOffset() + 5 * SceneData::GetInstance()->getGridSize())
		{
			m_go->active = false;
		}
	}
	//Distance check for patrol checkpoints
	else if ((m_go->pos - m_go->PatrolCheckpoints[m_go->patrolCheckpointIndex]).Length() < SceneData::GetInstance()->getGridOffset())
	{
		m_go->patrolCheckpointIndex++;
	}

	//Distance check for enemies
	timerEnemy += (float)dt;

	//Check if enemy is nearby
	if (timerEnemy > 1)
	{
		MessageWRU *msg = new MessageWRU(m_go, MessageWRU::NEAREST_ENEMY, 4 * SceneData::GetInstance()->getGridSize());
		PostOffice::GetInstance()->Send("Scene", msg);
		timerEnemy = 0;
	}

	//if there is enemy nearby
	if (m_go->targetGO)
	{
		//get grid Number;
		int XgridNum = (int)((m_go->pos.x - SceneData::GetInstance()->getGridOffset()) / SceneData::GetInstance()->getGridSize());
		int YgridNum = (int)((m_go->pos.y - SceneData::GetInstance()->getGridOffset()) / SceneData::GetInstance()->getGridSize());
		m_go->prevPos.Set(SceneData::GetInstance()->getGridOffset() + XgridNum * SceneData::GetInstance()->getGridSize(), SceneData::GetInstance()->getGridOffset() + YgridNum * SceneData::GetInstance()->getGridSize(), m_go->pos.z);
		m_go->sm->SetNextState("Attack");
	}
}

void StatePatrollerPatrolling::Exit()
{
}

//State Attacking
StatePatrollerAttacking::StatePatrollerAttacking(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StatePatrollerAttacking::~StatePatrollerAttacking()
{
}

void StatePatrollerAttacking::Enter()
{
	attackTimer = 0;
}

void StatePatrollerAttacking::Update(double dt)
{
	//Set to go back to previous location if target not found/dead
	if (!m_go->targetGO || m_go->targetGO->active == false || m_go->targetGO->sm->GetCurrentState() == "Destroyed" || m_go->targetGO->type != GameObject::GO_ENEMY )
	{
		m_go->targetGO = NULL;
		m_go->moveSpeed = 1;

		//Movement for going back
		m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
		float xDiff = m_go->pos.x - m_go->prevPos.x;
		if (xDiff < 0)
			xDiff = -xDiff;

		float yDiff = m_go->pos.y - m_go->prevPos.y;
		if (yDiff < 0)
			yDiff = -yDiff;

		if (xDiff > yDiff)
		{
			if (m_go->prevPos.x > m_go->pos.x)
				m_go->moveLeft = false;
			else
				m_go->moveRight = false;

			m_go->moveUp = m_go->moveDown = false;
		}
		else
		{
			if (m_go->prevPos.y > m_go->pos.y)
				m_go->moveDown = false;
			else
				m_go->moveUp = false;

			m_go->moveLeft = m_go->moveRight = false;
		}

		//switch back to patrol mode when reach location
		if ((m_go->pos - m_go->prevPos).Length() < SceneData::GetInstance()->getGridOffset())
		{
			m_go->sm->SetNextState("Patrol");
		}	
	}

	//If target out of range, chase after it
	else if ((m_go->pos - m_go->targetGO->pos).Length() > 6 * SceneData::GetInstance()->getGridSize())
	{
		m_go->moveSpeed = 1;

		//Movement for chasing
		m_go->moveLeft = m_go->moveRight = m_go->moveUp = m_go->moveDown = true;
		if (m_go->targetGO)
		{
			float xDiff = m_go->pos.x - m_go->targetGO->pos.x;
			if (xDiff < 0)
				xDiff = -xDiff;

			float yDiff = m_go->pos.y - m_go->targetGO->pos.y;
			if (yDiff < 0)
				yDiff = -yDiff;

			if (xDiff > yDiff)
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
	}
	else //Attack
	{
		m_go->moveSpeed = 0;

		//Attack every 0.5s
		attackTimer += (float)dt;
		if (attackTimer > 0.5f)
		{
			MessageSpawn *msg = new MessageSpawn(m_go, MessageSpawn::SPAWN_FRIENDLYBULLET);
			PostOffice::GetInstance()->Send("Scene", msg);
			attackTimer = 0;
		}
	}

	if (m_go->hp <= 0)
	{
		m_go->sm->SetNextState("Destroyed");
	}
}

void StatePatrollerAttacking::Exit()
{
}

//State Destroyed
StatePatrollerDestroyed::StatePatrollerDestroyed(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StatePatrollerDestroyed::~StatePatrollerDestroyed()
{
}

void StatePatrollerDestroyed::Enter()
{
	m_go->moveSpeed = 0;
	m_go->repairTime = 0;
}

void StatePatrollerDestroyed::Update(double dt)
{
	if (m_go->repairTime >= 5)
	{
		m_go->sm->SetNextState("Patrol");
		m_go->hp = 20;
	}
}

void StatePatrollerDestroyed::Exit()
{
}