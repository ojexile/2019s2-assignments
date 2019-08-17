#pragma once
#include "PlayerState.h"

class SprintingState :
	public PlayerState
{
private:
public:
	SprintingState();
	virtual ~SprintingState();

	virtual PlayerState* HandleInput(Component* com, double dt) override;
	virtual void OnEnter(Component* com) override;
};
