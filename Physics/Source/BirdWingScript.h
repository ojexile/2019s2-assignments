#pragma once
#include "ScriptComponent.h"
class BirdWingScript :
	public ScriptComponent
{
private:
	float m_fAngle;
	bool m_bUp;
public:
	BirdWingScript();
	virtual ~BirdWingScript();
	virtual Component* Clone() { return new BirdWingScript(*this); };
	virtual void Update(double dt) override;
};
