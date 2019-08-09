#include "GameObject.h"

GameObject::GameObject()
	: m_bActive{ true }
	, m_bStatic{ false }
{
	AddComponent(new TransformComponent);
}
// Copy
GameObject::GameObject(const GameObject& go)
{
	this->m_bActive = go.m_bActive;
	this->m_bStatic = go.m_bStatic;
	for (unsigned i = 0; i < go.m_vec_ComponentList.size(); ++i)
	{
		ComponentBase* cb = (go.m_vec_ComponentList[i]->Clone());
		cb->SetActive(go.m_vec_ComponentList[i]->IsActive());
		cb->SetStarted(go.m_vec_ComponentList[i]->IsStarted());
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
	for (unsigned i = 0; i < m_vec_ComponentList.size(); ++i)
	{
		delete m_vec_ComponentList.at(i);
	}
	//m_Transform = nullptr;
	for (unsigned i = 0; i < m_vec_ChildList.size(); ++i)
	{
		delete m_vec_ChildList[i];
	}
	// m_vec_ComponentList.clear();
	// m_vec_ChildList.clear();
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
	// Update components
	for (unsigned i = 0; i < m_vec_ComponentList.size(); ++i)
	{
		if (!m_vec_ComponentList[i]->IsActive())
		{
			continue;
		}
		m_vec_ComponentList[i]->CheckStarted();
		m_vec_ComponentList[i]->Update(dt);
		if (m_vec_ComponentList.size() <= 0)
			return;
	}
	for (unsigned i = 0; i < m_vec_ChildList.size(); ++i)
	{
		if (!m_vec_ChildList[i]->IsActive())
			continue;
		// Update world transform from relative trans
		// Update pos
		TransformComponent* trans = this->GetComponent<TransformComponent>();
		TransformComponent* childTrans = m_vec_ChildList[i]->GetComponent<TransformComponent>();

		Vector3 newPos = trans->GetPosition()
			+ childTrans->GetRelativePosition();
		// update rot pos
		if (trans->GetDegrees() != 0)
		{
			Mtx44 rot;
			rot.SetToRotation(trans->GetDegrees(), trans->GetRotation().x, trans->GetRotation().y, trans->GetRotation().z);
			newPos = trans->GetPosition() + rot * childTrans->GetRelativePosition();
		}
		m_vec_ChildList[i]->GetComponent<TransformComponent>()->SetPosition(newPos);
		// TODO update rot
		// Update scale
		Vector3 scale = trans->GetScale();
		Vector3 childScale = childTrans->GetRelativeScale();
		childTrans->SetScale({ scale.x * childScale.x, scale.y * childScale.y, scale.z * childScale.z });
		for (unsigned j = 0; j < m_vec_ChildList[i]->m_vec_ComponentList.size(); ++j)
		{
			if (!m_vec_ChildList[i]->m_vec_ComponentList[j]->IsActive())
				continue;
			ComponentBase* childcomp = m_vec_ChildList[i]->m_vec_ComponentList[j];
			if (childcomp->IsActive())
			{
				childcomp->CheckStarted();
				childcomp->Update(dt);
			}
			// Break if child destroys gameobject
			if (m_vec_ChildList.size() <= 0)
				return;
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
GameObject* GameObject::Clone() const
{
	GameObject* go = new GameObject(*this);
	return go;
}