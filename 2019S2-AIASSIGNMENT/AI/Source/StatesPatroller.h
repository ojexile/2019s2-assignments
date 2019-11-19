#ifndef STATES_PATROLLER_H
#define STATES_PATROLLER_H

#include "State.h"
#include "GameObject.h"

class StatePatrollerPatrolling : public State
{
	GameObject *m_go;
	float timerEnemy;
public:
	StatePatrollerPatrolling(const std::string &stateID, GameObject *go);
	virtual ~StatePatrollerPatrolling();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StatePatrollerAttacking : public State
{
	GameObject *m_go;
	float attackTimer;
public:
	StatePatrollerAttacking(const std::string &stateID, GameObject *go);
	virtual ~StatePatrollerAttacking();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StatePatrollerDestroyed : public State
{
	GameObject *m_go;
public:
	StatePatrollerDestroyed(const std::string &stateID, GameObject *go);
	virtual ~StatePatrollerDestroyed();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

#endif