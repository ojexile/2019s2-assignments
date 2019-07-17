#pragma once
#include "ScriptComponent.h"
#include "ScoreScript.h"
class GoalScript : public ScriptComponent
{
private:
	int m_iNumGoals;
	ScoreScript* m_ScoreScript;
public:
	GoalScript(ScoreScript* ScoreScript);
	virtual ~GoalScript();
	virtual ComponentBase* Clone()
	{
		return new GoalScript(*this);
	}

	virtual void Update(double dt) override;
	virtual void Collide(GameObject* go) override;
};
