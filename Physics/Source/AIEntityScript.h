#pragma once
#include "EntityScript.h"
#include "Behaviour.h"
#include "AIState.h"
class AIEntityScript : public EntityScript
{
private:
	AIState* m_CombatState; ///<	active state when ai is near player
public:
	AIEntityScript(Behaviour* Behaviour = nullptr, AIState* CombatState = nullptr);
	AIEntityScript(Behaviour* Behaviour, AIState* CombatState, Stats &Stats);
	AIEntityScript(AIEntityScript& ref);
	virtual ~AIEntityScript();
	virtual Component* Clone() { return new AIEntityScript(*this); };
	virtual void Update(double dt) override;

	AIState* GetCombatState();
};

