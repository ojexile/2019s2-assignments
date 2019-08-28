#pragma once
#include "AbilityBase.h"
class AbilityDash :
	public AbilityBase
{

public:
	AbilityDash(const float cooldowntime, const float cost);
	virtual ~AbilityDash();

	virtual void Use(Component* com);
	virtual void StopUse(Component* com);

	//virtual void Update(Component com);


};

