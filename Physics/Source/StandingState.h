#pragma once
#include "PlayerState.h"

class StandingState :
	public PlayerState
{
private:
	float m_fBaseMovementSpeed;
	float m_fBaseAccel;
	float m_fSprintMultiplier;
	float m_fCurrentBobOffset;

	float m_fDodgeForce;
public:
	StandingState();
	virtual ~StandingState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
};
