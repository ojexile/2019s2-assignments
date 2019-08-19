#pragma once
#include "AIState.h"
#include "StopWatch.h"
class IdleState :
	public AIState
{
private:
	StopWatch m_SW;
	float m_fTime;
public:
	IdleState();
	virtual ~IdleState();


	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new IdleState(*this); };
};

