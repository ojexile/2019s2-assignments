#pragma once
#include "ScriptComponent.h"
class BouncerScript : public ScriptComponent
{
private:
	float m_fBounceForce;
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
