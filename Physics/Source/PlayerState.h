#pragma once
#include "GameObject.h"
#include "State.h"
class PlayerState : public State
{
private:
public:
	PlayerState();
	virtual ~PlayerState();

	virtual State* HandleState(ComponentBase* com) = 0;
	virtual void OnEnter(ComponentBase* com) = 0;
	virtual void OnExit(ComponentBase* com) = 0;
};
