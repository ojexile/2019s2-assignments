#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
class ScriptComponent :
	public ComponentBase
{
protected:
	GameObject* Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle);
	GameObject* Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal);
	GameObject* Instantiate(GameObject* goRef, Vector3 pos);
	GameObject* Instantiate(GameObject* goRef);
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Start();
	virtual ComponentBase* Clone() = 0;
};
