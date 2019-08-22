#pragma once
#include "AIState.h"
#include "StopWatch.h"
class BossShockwaveState : public AIState
{
private:
	StopWatch s;
public:
	BossShockwaveState();
	virtual ~BossShockwaveState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new BossShockwaveState(*this); };
};
