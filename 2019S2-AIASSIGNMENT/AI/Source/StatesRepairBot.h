#ifndef STATES_REPAIRBOT_H
#define STATES_REPAIRBOT_H

#include "State.h"
#include "GameObject.h"

class StateRMoving : public State
{
	GameObject *m_go;
public:
	StateRMoving(const std::string &stateID, GameObject *go);
	virtual ~StateRMoving();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateRRepairing : public State
{
	GameObject *m_go;
public:
	StateRRepairing(const std::string &stateID, GameObject *go);
	virtual ~StateRRepairing();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateRAttacked : public State
{
	GameObject *m_go;
	float runTimer;
public:
	StateRAttacked(const std::string &stateID, GameObject *go);
	virtual ~StateRAttacked();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateRDestroyed : public State
{
	GameObject *m_go;
public:
	StateRDestroyed(const std::string &stateID, GameObject *go);
	virtual ~StateRDestroyed();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

#endif