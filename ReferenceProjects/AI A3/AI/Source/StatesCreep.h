#ifndef STATES_CREEP_H
#define STATES_CREEP_H

#include "State.h"
#include "GameObject.h"

class StateCMovement : public State
{
	GameObject *m_go;
public:
	StateCMovement(const std::string &stateID, GameObject *go);
	virtual ~StateCMovement();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateCAttack : public State
{
	GameObject *m_go;
	float timerAttack;
public:
	StateCAttack(const std::string &stateID, GameObject *go);
	virtual ~StateCAttack();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

#endif