#pragma once
#include "ScriptComponent.h"
#include "ScoreScript.h"
#define TRIGGER_DURATION 1.f
class BouncerScript : public ScriptComponent
{
private:
	float m_fBounceForce;
	bool m_bTriggered;
	float m_fTriggerTime;
	float m_fHealth;
	ScoreScript* m_ScoreScript;
	bool m_bIsPlayer;
public:
	BouncerScript(float bounceForce, ScoreScript* scoreScript, bool isPlayer = false);
	virtual ~BouncerScript();
	virtual ComponentBase* Clone()
	{
		return new BouncerScript(*this);
	}

	virtual void Update(double dt) override;
	virtual void Collide(GameObject* go) override;
};
