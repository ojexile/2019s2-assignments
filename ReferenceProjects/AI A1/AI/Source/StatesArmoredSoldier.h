#ifndef STATES_ARMOREDSOLDIER_H
#define STATES_ARMOREDSOLDIER_H

#include "State.h"
#include "GameObject.h"

class StateASPatrolling : public State
{
	GameObject *m_go;
	float timerEnemy;
public:
	StateASPatrolling(const std::string &stateID, GameObject *go);
	virtual ~StateASPatrolling();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateASAttacking : public State
{
	GameObject *m_go;
	float attackTimer;
public:
	StateASAttacking(const std::string &stateID, GameObject *go);
	virtual ~StateASAttacking();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateASDestroyed : public State
{
	GameObject *m_go;
public:
	StateASDestroyed(const std::string &stateID, GameObject *go);
	virtual ~StateASDestroyed();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

#endif