#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "ComponentBase.h"
#include "TransformComponent.h"
#include <vector>
#include <string>

#include "Locator.h"

class GameObject
{
private:
	bool m_bStatic;
	bool m_bActive;
	float m_fDisableDistance;
	std::vector<ComponentBase*> m_vec_ComponentList;
	std::vector<GameObject*> m_vec_ChildList;
	//Transform* m_Transform;
public:
	GameObject();
	GameObject(const GameObject& go);
	~GameObject();

	ComponentBase* AddComponent(ComponentBase* comp);
	bool IsActive();
	void SetDisableDistance(float f);
	float GetDisableDistance();
	void Update(double dt);

	// Duplicated from component
	template <class t>
	t* GetComponent(bool bOptional = false)
	{
		for (unsigned i = 0; i < m_vec_ComponentList.size(); ++i)
		{
			t* out = dynamic_cast<t*>(m_vec_ComponentList[i]);
			if (out)
				return out;
		}
		if (!bOptional)
		{
			std::string sTypeName = typeid(t).name();
			DEFAULT_LOG("Component of type " + sTypeName + " not found");
		}
		return nullptr;
	};
	void AddChild(GameObject* go);
	std::vector<GameObject*>* GetChildList();

	void SetActive(bool b);
	GameObject* Clone() const;

	friend class GameObjectManager;
};

#endif