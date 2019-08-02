#pragma once
#include "ScriptComponent.h"
#include "ChengPlayerScript.h"
class AmmoDumpScript : public ScriptComponent
{
public:
	AmmoDumpScript();
	virtual ~AmmoDumpScript();
	virtual ComponentBase* Clone() { return new AmmoDumpScript(*this); };
	virtual void Collide(GameObject* go) override;
};
