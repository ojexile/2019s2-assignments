#pragma once
#include "PlayerState.h"
#include "MovementCommand.h"

class TopDownState : public PlayerState
{
private:
	MovementCommand m_MovementCommand;
public:
	TopDownState();
	virtual ~TopDownState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new TopDownState(*this); };
};
