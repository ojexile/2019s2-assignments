#pragma once
#include "ScriptComponent.h"
class BlackholeScript :
	public ScriptComponent
{
private:
	float m_fMass;
	float m_fMinDist;
public:
	BlackholeScript(float fMass, float fMinDist);
	virtual ~BlackholeScript();
	virtual Component* Clone()
	{
		return new BlackholeScript(*this);
	}

	void Update(double dt) override;
};
