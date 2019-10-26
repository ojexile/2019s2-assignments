#ifndef STATES_HARVESTER_H
#define STATES_HARVESTER_H

#include "State.h"
#include "GameObject.h"

class StateHMoving : public State
{
	GameObject *m_go;
	float timerEnemy;
public:
	StateHMoving(const std::string &stateID, GameObject *go);
	virtual ~StateHMoving();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateHHarvesting : public State
{
	GameObject *m_go;
	float timerHarvest;
	float timerEnemy;
public:
	StateHHarvesting(const std::string &stateID, GameObject *go);
	virtual ~StateHHarvesting();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateHAttacked : public State
{
	GameObject *m_go;
	float timerEnemy;
public:
	StateHAttacked(const std::string &stateID, GameObject *go);
	virtual ~StateHAttacked();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateHDestroyed : public State
{
	GameObject *m_go;

public:
	StateHDestroyed(const std::string &stateID, GameObject *go);
	virtual ~StateHDestroyed();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};
#endif