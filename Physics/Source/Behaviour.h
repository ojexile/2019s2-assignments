#pragma once
#include "State.h"
#include "ComponentBase.h"
#include "AIState.h"
class Behaviour
{
private:
	ComponentBase* m_Com;
	State* m_CurrentState;
	bool m_bStarted;

	// AI--------------------------------------------------------------------------------
	AIState* m_CombatState; ///<	active state when ai is near player
	AIState* m_WanderState; ///<	active state when ai is near player
	AIState* m_IdleState; ///<	active state when ai is near player
public:
	Behaviour(State* InitialState, AIState* c = nullptr, AIState* w = nullptr,
		AIState* i = nullptr);
	Behaviour(Behaviour &ref);
	void Init(ComponentBase* com);
	virtual ~Behaviour();

	void Update();

	AIState* GetCombatState();
	AIState* GetWanderState();
	AIState* GetIdleState();
};
