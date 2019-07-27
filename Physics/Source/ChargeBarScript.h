#pragma once
#include "ScriptComponent.h"
#include "GauntletScript.h"
class ChargeBarScript :
	public ScriptComponent
{
private:
	const GauntletScript* m_GS;
	GameObject* m_Part;
public:
	ChargeBarScript(GauntletScript* GS, GameObject* Part);
	virtual ~ChargeBarScript();
	virtual ComponentBase* Clone() { return new ChargeBarScript(*this); };

	virtual void Update(double dt) override;
};
