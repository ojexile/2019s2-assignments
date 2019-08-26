#pragma once
#include "AbilityBase.h"
class AbilitySlowTime :
	public AbilityBase
{
private:
	float m_fOffset;
	const float m_fMaxOffset;
	float m_fOverrideTimeScale;
	bool m_bOneTimeTrigger;
public:
	AbilitySlowTime(const float usetime, const float cooldowntime, const float cost, float maxoffset = 5.f, float timescale = 0.5f);
	~AbilitySlowTime();

	virtual void Use(Component* com);
	virtual void StopUse(Component* com);

	//virtual void Update(Component* com);
};

