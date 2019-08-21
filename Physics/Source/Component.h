#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
#include "Vector3.h"

class Component : public ComponentBase
{
protected:
	std::vector<GameObject*>* m_vec_RefChildList;
	GameObject* m_ParentGO;
public:
	Component();
	virtual ~Component();

	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default", bool bIsChild = false) const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, std::string sLayer = "Default") const;
	void Destroy(GameObject* go);
	void DestroySelf();
	void Init(std::vector<GameObject*>* ChildRef, GameObject* Parent);
	Vector3 GetPosition();
	GameObject* GetChild(int i);
};
