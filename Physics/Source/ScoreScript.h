#pragma once
#include "ScriptComponent.h"
class ScoreScript : public ScriptComponent
{
private:
	int m_iScore;
public:
	ScoreScript();
	virtual ~ScoreScript();

	virtual ComponentBase* Clone()
	{
		return new ScoreScript(*this);
	}

	void IncrementScore(int i);
	virtual void Update(double dt) override;
};
