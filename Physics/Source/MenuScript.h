#pragma once
#include "ScriptComponent.h"
class MenuScript :
	public ScriptComponent
{
public:
	MenuScript();
	virtual ~MenuScript();
	virtual ComponentBase* Clone() { return new MenuScript(*this); };

	virtual void Update(double dt) override;
};
