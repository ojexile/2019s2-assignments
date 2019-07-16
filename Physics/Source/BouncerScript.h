#pragma once
#include "ScriptComponent.h"
#define TRIGGER_DURATION 1.f
class BouncerScript : public ScriptComponent
{
private:
	float m_fBounceForce;
	bool m_bTriggered;
	float m_fTriggerTime;
public:
	BouncerScript(float bounceForce);
	virtual ~BouncerScript();
	virtual ComponentBase* Clone()
	{
		return new BouncerScript(*this);
	}

	virtual void Update(double dt) override;
	virtual void Collide(GameObject* go) override;
};
