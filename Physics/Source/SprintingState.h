#pragma once
#include "PlayerState.h"

class SprintingState :
	public PlayerState
{
private:
public:
	SprintingState();
	virtual ~SprintingState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
};
