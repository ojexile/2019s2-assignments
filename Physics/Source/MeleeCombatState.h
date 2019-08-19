#pragma once
#include "AIState.h"
#include "GameObject.h"

class MeleeCombatState :
	public AIState
{
private:
	GameObject* m_Player;
public:
	MeleeCombatState();
	virtual ~MeleeCombatState();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new MeleeCombatState(*this); };
};

