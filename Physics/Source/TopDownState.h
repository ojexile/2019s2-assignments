#pragma once
#include "PlayerState.h"

class TopDownState :
	public PlayerState
{
private:
public:
	TopDownState();
	virtual ~TopDownState();

	virtual PlayerState* HandleInput(ComponentBase* com, double dt) override;
	virtual void OnEnter(ComponentBase* com) override;
};
