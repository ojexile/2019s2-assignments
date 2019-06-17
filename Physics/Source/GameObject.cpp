#include "GameObject.h"

GameObject::GameObject()
{
	m_bActive = true;
	m_Transform = new Transform;
	AddComponent(m_Transform);
}

GameObject::~GameObject()
{
}
bool GameObject::AddComponent(ComponentBase* comp)
{
	// TODO check if component already exists?
	// Should there be duplicate components?
	comp->Init(&m_vec_ComponentList);
	m_vec_ComponentList.push_back(comp);
	return true;
}

bool GameObject::IsActive()
{
	return m_bActive;
}

Transform* GameObject::GetTransform()
{
	return m_Transform;
}