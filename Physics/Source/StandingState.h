#pragma once
#include "PlayerState.h"
#include "MovementCommand.h"
class StandingState : public PlayerState
{
private:
	float m_fMovementBoost;
	float m_fForrceBoost;

	MovementCommand m_MovementCommand;
public:
	StandingState();
	virtual ~StandingState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
};
