#pragma once
#include "AIState.h"
class WanderState :
	public AIState
{
public:
	WanderState();
	virtual ~WanderState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
};

