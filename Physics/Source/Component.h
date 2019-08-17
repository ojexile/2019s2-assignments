#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
#include "Vector3.h"

class Component : public ComponentBase
{
public:
	Component();
	virtual ~Component();

	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default", bool bIsChild = false) const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, std::string sLayer = "Default") const;
	void Destroy(GameObject* go);
	void DestroySelf();

	Vector3 GetPosition();
};
