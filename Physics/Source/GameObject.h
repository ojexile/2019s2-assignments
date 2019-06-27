#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "ComponentBase.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include <vector>
#include <string>

#include "Locator.h"

class GameObject
{
private:
	bool m_bStatic;
	bool m_bActive;
	std::vector<ComponentBase*> m_vec_ComponentList;
	//Transform* m_Transform;
public:
	GameObject();
	~GameObject();

	ComponentBase* AddComponent(ComponentBase* comp);
	bool IsActive();
	//Transform* GetTransform();

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
		std::string sTypeName = typeid(t).name();
		// Locator::GetLogger(Locator::CHENG).Log("No component of type " + sTypeName + " found.");
		if (!bOptional)
			DEFAULT_LOG("Component of type " + sTypeName + " not found");
		return nullptr;
	};
};

#endif