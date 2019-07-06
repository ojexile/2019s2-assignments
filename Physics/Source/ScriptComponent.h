#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
class ScriptComponent :
	public ComponentBase
{
protected:
	GameObject* Instantiate(GameObject* goRef, Vector3 pos = {}, Vector3 vRot = {}, Vector3 vScal = { 1,1,1 });
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Start();
	virtual ComponentBase* Clone() = 0;
};
