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

	virtual PlayerState* HandleInput(Component* com, double dt) override;
	virtual void OnEnter(Component* com) override;
};
