#pragma once
#include "AbilityBase.h"
class AbilityHeal :
	public AbilityBase
{
private:
	bool m_bIsHealing;
	float m_fHealRate;
	float m_fprevtime;
public:
	AbilityHeal(const float usetime, const float cooldown, const float cost, float totalhealedamount = 20.f);
	virtual~AbilityHeal();

	virtual void Use(Component* com);
	virtual void StopUse(Component* com);
	virtual void Update(Component* com);


};

