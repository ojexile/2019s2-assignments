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
	Vector3 m_vTarget;
	Vector3 m_vPrevPos;
	bool m_bFirstMove;
	bool m_bAgainstWall;
public:
	AIEntityScript(Behaviour* Behaviour = nullptr);
	AIEntityScript(Behaviour* Behaviour, Stats &Stats);
	AIEntityScript(AIEntityScript& ref);
	virtual ~AIEntityScript();
	virtual Component* Clone() { return new AIEntityScript(*this); };
	virtual void Update(double dt) override;
	void SetAgainstWall(bool b);

	void SetTarget(Vector3 v);
	void MoveToTarget();
};
