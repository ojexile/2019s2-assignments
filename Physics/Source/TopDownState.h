#pragma once
#include "PlayerState.h"

class TopDownState :
	public PlayerState
{
private:
public:
	TopDownState();
	virtual ~TopDownState();

	virtual PlayerState* HandleInput(Component* com, double dt) override;
	virtual void OnEnter(Component* com) override;
};
