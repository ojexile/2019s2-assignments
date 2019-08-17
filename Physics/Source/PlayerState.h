#pragma once
#include "GameObject.h"
class PlayerState
{
private:
public:
	PlayerState();
	virtual ~PlayerState();

	virtual PlayerState* HandleInput(Component* com, double dt) = 0;
	virtual void OnEnter(Component* com) = 0;
};
