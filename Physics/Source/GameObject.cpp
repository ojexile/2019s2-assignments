#include "GameObject.h"

GameObject::GameObject()
{
	m_bActive = true;
	m_bStatic = false;
	//m_Transform = new Transform;
	AddComponent(new TransformComponent);
}
// Copy
GameObject::GameObject(GameObject& go)
{
	this->m_bActive = go.m_bActive;
	this->m_bStatic = go.m_bStatic;
	for (unsigned i = 0; i < go.m_vec_ComponentList.size(); ++i)
	{
		ComponentBase* cb = (go.m_vec_ComponentList[i]->Clone());
		this->AddComponent(cb);
	}
	for (unsigned i = 0; i < go.m_vec_ChildList.size(); ++i)
	{
		GameObject* child = go.m_vec_ChildList[i]->Clone();
		m_vec_ChildList.push_back(child);
	}
}

GameObject::~GameObject()
{
	// Clear components
	for (int i = (int)m_vec_ComponentList.size() - 1; i >= 0; --i)
	{
		delete m_vec_ComponentList[i];
		m_vec_ComponentList.erase(m_vec_ComponentList.begin() + i);
	}
	//m_Transform = nullptr;
	for (int i = (int)m_vec_ChildList.size() - 1; i >= 0; --i)
	{
		delete m_vec_ChildList[i];
		m_vec_ChildList.erase(m_vec_ChildList.begin() + i);
	}
}
ComponentBase* GameObject::AddComponent(ComponentBase* comp)
{
	// TODO check if component already exists?
	// Should there be duplicate components?
	comp->Init(&m_vec_ComponentList);
	m_vec_ComponentList.push_back(comp);
	return comp;
}

bool GameObject::IsActive()
{
	return m_bActive;
}

void GameObject::Update(double dt)
{
	for (unsigned i = 0; i < m_vec_ComponentList.size(); ++i)
	{
		m_vec_ComponentList[i]->Update(dt);
	}
	for (unsigned i = 0; i < m_vec_ChildList.size(); ++i)
	{
		// Update pos
		m_vec_ChildList[i]->GetComponent<TransformComponent>()
			->SetPosition(
				this->GetComponent<TransformComponent>()->GetPosition()
				+ m_vec_ChildList[i]->GetComponent<TransformComponent>()->GetRelativePosition());
		for (unsigned j = 0; j < m_vec_ChildList[i]->m_vec_ComponentList.size(); ++j)
		{
			m_vec_ChildList[i]->m_vec_ComponentList[j]->Update(dt);
		}
	}
}
void GameObject::AddChild(GameObject* go)
{
	m_vec_ChildList.push_back(go);
}
std::vector<GameObject*>* GameObject::GetChildList()
{
	return &m_vec_ChildList;
}
void GameObject::SetActive(bool b)
{
	m_bActive = b;
}
GameObject* GameObject::Clone()
{
	GameObject* go = new GameObject(*this);
	return go;
}