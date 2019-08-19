#pragma once
#include "AIState.h"
class FleeState :
	public AIState
{
public:
	FleeState(State* Combat);
	virtual ~FleeState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new FleeState(*this); };
};
