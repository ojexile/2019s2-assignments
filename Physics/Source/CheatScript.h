#pragma once
#include "ScriptComponent.h"
class CheatScript :
	public ScriptComponent
{
public:
	CheatScript();
	virtual ~CheatScript();
	virtual Component* Clone() { return new CheatScript(*this); };
	virtual void Update(double dt) override;
};
