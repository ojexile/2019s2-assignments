#pragma once
#include "AIState.h"
#include "StopWatch.h"
class WanderState :
	public AIState
{
private:
	StopWatch m_SW;
	float m_fTime;
	Vector3 m_vDir;
	float m_fMinTime;
	float m_fMaxTime;
	AIState* m_Idle;
public:
	WanderState(AIState* idle, float min = 1, float max = 5);
	virtual ~WanderState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new WanderState(*this); };
};
