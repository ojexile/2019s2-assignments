#ifndef STATES_Enemy_H
#define STATES_Enemy_H

#include "State.h"
#include "GameObject.h"

class StateEMoving : public State
{
	GameObject *m_go;
public:
	StateEMoving(const std::string &stateID, GameObject *go);
	virtual ~StateEMoving();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateEAttacking : public State
{
	GameObject *m_go;
	float attackTimer;
public:
	StateEAttacking(const std::string &stateID, GameObject *go);
	virtual ~StateEAttacking();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateEDestroyed : public State
{
	GameObject *m_go;
public:
	StateEDestroyed(const std::string &stateID, GameObject *go);
	virtual ~StateEDestroyed();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

#endif