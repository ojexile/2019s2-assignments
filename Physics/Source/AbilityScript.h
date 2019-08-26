#pragma once
#include "ScriptComponent.h"
#include "AbilityBase.h"

class AbilityScript : public ScriptComponent
{
private:
	AbilityBase* m_ability;

public:
	AbilityScript();
	AbilityScript(AbilityBase* Ability);
	~AbilityScript();
	
	Component* Clone() { return new AbilityScript(*this); }
	virtual void Update(double dt);


};