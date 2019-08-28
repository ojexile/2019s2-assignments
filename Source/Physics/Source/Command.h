#pragma once
#include "ComponentBase.h"
class Command
{
public:
	Command();
	virtual ~Command();

	virtual void HandleCommand(ComponentBase* com) = 0;
};

