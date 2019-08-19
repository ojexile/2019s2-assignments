#pragma once
#include "PlayerState.h"

class TopDownState : public PlayerState
{
private:
public:
	TopDownState();
	virtual ~TopDownState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
};
