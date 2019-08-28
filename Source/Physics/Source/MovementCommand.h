#pragma once
#include "Command.h"


class MovementCommand :
	public Command
{
public:
	MovementCommand();
	virtual ~MovementCommand();

	void HandleCommand(ComponentBase* com) override;
};

