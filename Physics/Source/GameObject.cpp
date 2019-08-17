#include "GameObject.h"
#include "SceneManager.h"
#include "Mtx44.h"

GameObject::GameObject()
	: m_bActive{ true }
	, m_bStatic{ false }
{
	AddComponent(new TransformComponent);
	m_fDisableDistance = 2000000;
}
// Copy
GameObject::GameObject(const GameObject& go)
{
	this->m_bActive = go.m_bActive;
	this->m_bStatic = go.m_bStatic;
	m_fDisableDistance = 2000000;
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

void GameObject::SetDisableDistance(float f)
{
	m_fDisableDistance = f;
}

float GameObject::GetDisableDistance()
{
	return m_fDisableDistance;
}

void GameObject::Update(double dt)
{
	if (m_fDisableDistance < (SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition() - TRANS->GetPosition()).Length())
		return;
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
		GameObject* go2 = m_vec_ChildList[i];
		if (!go2->IsActive())
			continue;
		// Update world transform from relative trans
		// Update pos
		TransformComponent* rootTrans = this->GetComponent<TransformComponent>();
		TransformComponent* childTrans = go2->GetComponent<TransformComponent>();

		Vector3 newPos = rootTrans->GetPosition()
			+ childTrans->GetRelativePosition();
		// update rot pos
		if (rootTrans->GetDegrees() != 0)
		{
			Mtx44 rot;
			rot.SetToRotation(rootTrans->GetDegrees(), rootTrans->GetRotation().x, rootTrans->GetRotation().y, rootTrans->GetRotation().z);
			newPos = rootTrans->GetPosition() + rot * childTrans->GetRelativePosition();
			// update rot
			childTrans->SetRotation(rootTrans->GetDegrees(), rootTrans->GetRotation().x, rootTrans->GetRotation().y, rootTrans->GetRotation().z);
		}
		go2->GetComponent<TransformComponent>()->SetPosition(newPos);
		// Update scale
		Vector3 scale = rootTrans->GetScale();
		Vector3 childScale = childTrans->GetRelativeScale();
		childTrans->SetScale({ scale.x * childScale.x, scale.y * childScale.y, scale.z * childScale.z });
		for (unsigned j = 0; j < go2->m_vec_ComponentList.size(); ++j)
		{
			if (!go2->m_vec_ComponentList[j]->IsActive())
				continue;
			ComponentBase* childcomp = go2->m_vec_ComponentList[j];
			if (childcomp->IsActive())
			{
				childcomp->CheckStarted();
				childcomp->Update(dt);
			}
			// Break if child destroys gameobject
			if (m_vec_ChildList.size() <= 0)
				return;
		}
		for (unsigned k = 0; k < go2->m_vec_ChildList.size(); ++k)
		{
			GameObject* go3 = go2->m_vec_ChildList[k];
			if (!go3->IsActive())
				continue;
			// Update world transform from relative trans
			// Update pos
			TransformComponent* trans = go2->GetComponent<TransformComponent>();
			TransformComponent* childTrans = go3->GetComponent<TransformComponent>();

			Vector3 newPos = trans->GetPosition()
				+ childTrans->GetRelativePosition();
			// update rot pos
			if (trans->GetDegrees() != 0)
			{
				Mtx44 rot;
				rot.SetToRotation(trans->GetDegrees(), trans->GetRotation().x, trans->GetRotation().y, trans->GetRotation().z);
				newPos = trans->GetPosition() + rot * childTrans->GetRelativePosition();
				// update rot
				childTrans->SetRotation(trans->GetDegrees(), trans->GetRotation().x, trans->GetRotation().y, trans->GetRotation().z);
			}
			go3->GetComponent<TransformComponent>()->SetPosition(newPos);
			// Update scale
			Vector3 scale = trans->GetScale();
			Vector3 childScale = childTrans->GetRelativeScale();
			childTrans->SetScale({ scale.x * childScale.x, scale.y * childScale.y, scale.z * childScale.z });
			for (unsigned l = 0; l < go3->m_vec_ComponentList.size(); ++l)
			{
				if (!go3->m_vec_ComponentList[l]->IsActive())
					continue;
				ComponentBase* childcomp = go3->m_vec_ComponentList[l];
				if (childcomp->IsActive())
				{
					childcomp->CheckStarted();
					childcomp->Update(dt);
				}
				// Break if child destroys gameobject
				if (go2->m_vec_ChildList.size() <= 0)
					return;
			}
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