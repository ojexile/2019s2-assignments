#ifndef STATES_MONSTER_H
#define STATES_MONSTER_H

#include "State.h"
#include "GameObject.h"

class StateMMoving : public State
{
	GameObject *m_go;
public:
	StateMMoving(const std::string &stateID, GameObject *go);
	virtual ~StateMMoving();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateMAttack : public State
{
	GameObject *m_go;
public:
	StateMAttack(const std::string &stateID, GameObject *go);
	virtual ~StateMAttack();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};
#endif