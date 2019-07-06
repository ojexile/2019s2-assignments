#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
class ScriptComponent :
	public ComponentBase
{
protected:
	GameObject* Instantiate(GameObject* goRef, Vector3 pos = {}, Vector3 vScal = { 1,1,1 }, Vector3 vRot = {}, float fAngle = 0);
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Start();
	virtual ComponentBase* Clone() = 0;
};
