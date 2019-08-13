#pragma once
#include "ScriptComponent.h"
class ReticleScript :
	public ScriptComponent
{
public:
	ReticleScript();
	virtual ~ReticleScript();

	virtual ComponentBase* Clone() { return new ReticleScript(*this); };

	void Update(double dt) override;
};

