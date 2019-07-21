#pragma once
#include "ScriptComponent.h"
class SunBrightnessScript :
	public ScriptComponent
{
public:
	SunBrightnessScript();
	virtual ~SunBrightnessScript();
	virtual ComponentBase* Clone() { return new SunBrightnessScript(*this); };
	virtual void Update(double dt) override;
};
