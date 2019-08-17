#pragma once
#include "PlayerState.h"

class CrouchingState :
	public PlayerState
{
private:
	float m_fBaseMovementSpeed;
	float m_fTimer;
public:
	CrouchingState();
	virtual ~CrouchingState();

	virtual PlayerState* HandleInput(Component* com, double dt) override;
	virtual void OnEnter(Component* com) override;
};
