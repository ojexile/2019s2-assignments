#pragma once
#include "ScriptComponent.h"
class ReloadUIScript :
	public ScriptComponent
{
public:
	ReloadUIScript();
	virtual ~ReloadUIScript();
	virtual Component* Clone() { return new ReloadUIScript(*this); };
	virtual void Update(double dt) override;
	virtual void Start() override;
};
