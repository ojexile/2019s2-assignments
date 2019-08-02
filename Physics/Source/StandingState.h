#pragma once
#include "PlayerState.h"
#define STANDING_HEIGHT 10.f
class StandingState :
	public PlayerState
{
private:
	float m_fBaseMovementSpeed;
	float m_fBaseAccel;
	float m_fSprintMultiplier;
	float m_fCurrentBobOffset;
public:
	StandingState();
	virtual ~StandingState();

	virtual PlayerState* HandleInput(ComponentBase* com, double dt) override;
	virtual void OnEnter(ComponentBase* com) override;
};
