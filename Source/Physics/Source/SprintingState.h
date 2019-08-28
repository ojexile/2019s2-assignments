#pragma once
#include "PlayerState.h"
#include "MovementCommand.h"

class SprintingState :
	public PlayerState
{
private:
	MovementCommand m_MovementCommand;
public:
	SprintingState();
	virtual ~SprintingState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new SprintingState(*this); };
};
