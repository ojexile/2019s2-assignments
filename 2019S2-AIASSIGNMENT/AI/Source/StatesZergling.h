#ifndef STATES_ZERGLING_H
#define STATES_ZERGLING_H

#include "State.h"
#include "GameObject.h"

class StateZMoving : public State
{
	GameObject *m_go;
	float timerEnemy;
public:
	StateZMoving(const std::string &stateID, GameObject *go);
	virtual ~StateZMoving();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateZAttacking : public State
{
	GameObject *m_go;
	float attackTimer;
public:
	StateZAttacking(const std::string &stateID, GameObject *go);
	virtual ~StateZAttacking();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateZDestroyed : public State
{
	GameObject *m_go;
public:
	StateZDestroyed(const std::string &stateID, GameObject *go);
	virtual ~StateZDestroyed();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};
#endif