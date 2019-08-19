#pragma once
#include "State.h"
class AIState :
	public State
{
public:
	AIState();
	virtual ~AIState();

	virtual State* HandleState(ComponentBase* com) = 0;
	virtual void OnEnter(ComponentBase* com) = 0;
	virtual void OnExit(ComponentBase* com) = 0;
};

