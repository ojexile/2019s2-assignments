#pragma once
#include "AIState.h"
#include "StopWatch.h"
class IdleState :
	public AIState
{
private:
	StopWatch m_SW;
	float m_fTime;
	float m_fMinTime;
	float m_fMaxTime;
public:
	IdleState(float min = 0, float max = 0.1f);
	virtual ~IdleState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new IdleState(*this); };
};