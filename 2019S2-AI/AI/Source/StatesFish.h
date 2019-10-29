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

#endif