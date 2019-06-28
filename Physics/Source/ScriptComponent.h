#pragma once
#include "ComponentBase.h"
class ScriptComponent :
	public ComponentBase
{
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt) = 0;
	virtual void Start() = 0;
};
