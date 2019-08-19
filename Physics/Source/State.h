#pragma once
#include "ComponentBase.h"
class State
{
public:
	State();
	virtual ~State();

	virtual State* HandleState(ComponentBase* com) = 0;
	virtual void OnEnter(ComponentBase* com) = 0;
	virtual void OnExit(ComponentBase* com) = 0;
	virtual State* Clone() = 0;
};

