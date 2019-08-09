#pragma once
#include "ScriptComponent.h"
class FPSScript :public ScriptComponent
{
private:
	RenderComponent* rc;
public:
	FPSScript();
	virtual ~FPSScript();
	virtual ComponentBase* Clone() { return new FPSScript(*this); };

	virtual void Update(double dt);
	virtual void Start() override;
};
