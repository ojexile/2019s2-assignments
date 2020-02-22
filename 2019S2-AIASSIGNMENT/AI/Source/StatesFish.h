#ifndef STATES_FISH_H
#define STATES_FISH_H

#include "State.h"
#include "GameObject.h"

class StateTooFull : public State
{
	GameObject *m_go;
public:
	StateTooFull(const std::string &stateID, GameObject *go);
	virtual ~StateTooFull();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateFull : public State
{
	GameObject *m_go;
	float timer;
public:
	StateFull(const std::string &stateID, GameObject *go);
	virtual ~StateFull();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateHungry : public State
{
	GameObject *m_go;
public:
	StateHungry(const std::string &stateID, GameObject *go);
	virtual ~StateHungry();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateDead : public State
{
	GameObject *m_go;
public:
	StateDead(const std::string &stateID, GameObject *go);
	virtual ~StateDead();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};
#endif