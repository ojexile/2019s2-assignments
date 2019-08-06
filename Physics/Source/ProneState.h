#pragma once
#include "PlayerState.h"

class ProneState :
	public PlayerState
{
private:
	float m_fBaseMovementSpeed;
public:
	ProneState();
	virtual ~ProneState();

	virtual PlayerState* HandleInput(ComponentBase* com, double dt) override;
	virtual void OnEnter(ComponentBase* com) override;
};
