#ifndef STATES_FISHFOOD_H
#define STATES_FISHFOOD_H

#include "State.h"
#include "GameObject.h"

class StateGrow : public State
{
	GameObject *m_go;
	float timer;
public:
	StateGrow(const std::string &stateID, GameObject *go);
	virtual ~StateGrow();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateEvolve : public State
{
	GameObject *m_go;
public:
	StateEvolve(const std::string &stateID, GameObject *go);
	virtual ~StateEvolve();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};
#endif