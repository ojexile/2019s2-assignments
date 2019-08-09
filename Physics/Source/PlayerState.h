#pragma once
#include "GameObject.h"
class PlayerState
{
private:
public:
	PlayerState();
	virtual ~PlayerState();

	virtual PlayerState* HandleInput(ComponentBase* com, double dt) = 0;
	virtual void OnEnter(ComponentBase* com) = 0;
};
