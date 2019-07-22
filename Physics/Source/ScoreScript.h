#pragma once
#include "ScriptComponent.h"
class ScoreScript : public ScriptComponent
{
private:
	static int m_iScore;
	static int m_iDestroyed;
	static int m_iCurrentLevel;
public:
	ScoreScript();
	virtual ~ScoreScript();

	virtual ComponentBase* Clone()
	{
		return new ScoreScript(*this);
	}

	void IncrementScore(int i);
	void ObjectDestroyed();
	virtual void Update(double dt) override;
};
