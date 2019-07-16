#pragma once
#include "ScriptComponent.h"
class GoalScript : public ScriptComponent
{
private:
	int m_iNumGoals;
public:
	GoalScript();
	virtual ~GoalScript();
	virtual ComponentBase* Clone()
	{
		return new GoalScript(*this);
	}

	virtual void Update(double dt) override;
	virtual void Collide(GameObject* go) override;
};
