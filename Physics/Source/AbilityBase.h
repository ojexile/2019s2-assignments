#pragma once
#include "StopWatch.h"
#include "Component.h"
/*
author: lorenzo yanga
desc: ability base class.
*/
class AbilityBase
{
protected:
	const float m_fUseTime; // duration of ability (if any)
	const float m_fCooldownTime; // cooldown time (after useTime)
	StopWatch m_SW; // use this to keep track of the time
	bool m_bCanUse;
	bool m_bInUse;
	const float m_fStaminaCost;

public:
	AbilityBase(const float usetime, const float cooldowntime, const float cost);
	virtual ~AbilityBase();

	virtual void Use(Component* com) = 0;
	virtual void StopUse(Component* com) = 0;

	virtual void Update(Component* com);

	bool CanUse();
	bool IsInUse();

};