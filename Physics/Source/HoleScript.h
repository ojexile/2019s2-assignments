#pragma once
#include "ScriptComponent.h"
class HoleScript : public ScriptComponent
{
public:
	HoleScript();
	~HoleScript();
	virtual ComponentBase* Clone() { return new HoleScript(*this); };
	virtual void Collide(GameObject* go) override;
};
