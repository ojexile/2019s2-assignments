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

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new CrouchingState(*this); };
};
