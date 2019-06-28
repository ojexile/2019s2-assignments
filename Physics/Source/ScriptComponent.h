#pragma once
#include "ComponentBase.h"
class ScriptComponent :
	public ComponentBase
{
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Start();
};
