#pragma once
#include "PlayerState.h"

class SprintingState :
	public PlayerState
{
private:
public:
	SprintingState();
	virtual ~SprintingState();

	virtual PlayerState* HandleInput(ComponentBase* com, double dt) override;
	virtual void OnEnter(ComponentBase* com) override;
};
