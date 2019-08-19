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
public:
	WanderState();
	virtual ~WanderState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new WanderState(*this); };
};
