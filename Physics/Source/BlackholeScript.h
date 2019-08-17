#pragma once
#include "ScriptComponent.h"
class Blackhole :
	public ScriptComponent
{
private:
	float m_fMass;
	float m_fMinDist;
public:
	Blackhole(float fMass, float fMinDist);
	virtual ~Blackhole();
	virtual Component* Clone()
	{
		return new Blackhole(*this);
	}

	void Update(double dt) override;
};
