#pragma once
#include "PlayerState.h"
#define CROUCHING_HEIGHT 0.9f
class CrouchingState :
	public PlayerState
{
private:
	float m_fBaseMovementSpeed;
public:
	CrouchingState();
	virtual ~CrouchingState();

	virtual PlayerState* HandleInput(ComponentBase* com, double dt) override;
	virtual void OnEnter(ComponentBase* com) override;
};
