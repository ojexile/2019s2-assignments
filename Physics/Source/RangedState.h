#pragma once
#include "AIState.h"
#include "GameObject.h"

class RangedState :
	public AIState
{
private:
public:
	RangedState();
	virtual ~RangedState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new RangedState(*this); };
};
