#pragma once
#include "ScriptComponent.h"
class StaminaScript :
	public ScriptComponent
{
private:
	float m_fStamina;
	GameObject* m_Stam;
public:
	StaminaScript(GameObject* stam);
	virtual ~StaminaScript();
	virtual void Update(double dt) override;
	virtual ComponentBase* Clone() { return new StaminaScript(*this); };
	void DrainStamina(float f);
	float GetStamina();
};
