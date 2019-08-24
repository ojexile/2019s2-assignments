#pragma once
#include "ScriptComponent.h"
class PlayerDeathScript :
	public ScriptComponent
{
public:
	PlayerDeathScript();
	virtual ~PlayerDeathScript();
	virtual Component* Clone() { return new PlayerDeathScript(*this); };

	virtual void Start() override;
	virtual void Update(double dt) override;
};
