#include "ComponentBase.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "GenericSubject.h"
#include "TransformComponent.h"
Component::Component()
	: m_vec_RefList{ nullptr }
	, m_bStarted{ false }
	, m_bActive{ true }
{
	m_bStarted = false;
}
Component::Component(Component& com)
{
	m_vec_RefList = nullptr;
}
Component::~Component()
{
	//DEFAULT_LOG("Default component destructor called. Ensure your concrete component's destructor is virtual.");
}

void Component::Init(std::vector<Component*>* refList)
{
	m_vec_RefList = refList;
}
void Component::Update(double dt)
{
	DEFAULT_LOG("Default update called.");
}
void Component::CheckStarted()
{
	if (!m_bStarted)
	{
		Start();
		m_bStarted = true;
	}
}
void Component::Start()
{
	return;
}

bool Component::IsActive()
{
	return m_bActive;
}
void Component::SetActive(bool b)
{
	m_bActive = b;
}
bool Component::IsStarted()
{
	return m_bStarted;
}
void Component::SetStarted(bool b)
{
	m_bStarted = b;
}
void Component::Notify(Component* com, std::string msg)
{
	GenericSubject::GetInstance()->NotifySubject(com, msg);
}
Vector3 Component::GetPosition()
{
	return GetComponent<TransformComponent>()->GetPosition();
}