#pragma once
#include "ScriptComponent.h"
#include "AbilityBase.h"

/*
author: lorenzo yanga
desc; ability script class that acts as the bridge between the abilitybase class and the components
*/

class AbilityScript : public ScriptComponent
{
private:
	AbilityBase* m_ability;
	GameObject* m_UI;
public:
	AbilityScript(AbilityBase* Ability, GameObject* UI);
	~AbilityScript();

	Component* Clone() { return new AbilityScript(*this); }
	virtual void Update(double dt);

	float GetPercentageCooldownDone();
};