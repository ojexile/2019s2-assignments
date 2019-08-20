#pragma once
#include "EntityScript.h"
#include "Behaviour.h"
#include "AIState.h"
#include "ComponentMacros.h"
#include "RenderComponent.h"
class AIEntityScript : public EntityScript
{
public:
	enum eTargetType
	{
		eDIR,
		ePOS,
	};
private:
	int m_iCounter;
	AIState* m_CombatState; ///<	active state when ai is near player
	Vector3 m_vTarget;
public:
	AIEntityScript(Behaviour* Behaviour = nullptr, AIState* CombatState = nullptr);
	AIEntityScript(Behaviour* Behaviour, AIState* CombatState, Stats &Stats);
	AIEntityScript(AIEntityScript& ref);
	virtual ~AIEntityScript();
	virtual Component* Clone() { return new AIEntityScript(*this); };
	virtual void Update(double dt) override;

	AIState* GetCombatState();
	void SetTarget(Vector3 v);
	void MoveToTarget();
};
