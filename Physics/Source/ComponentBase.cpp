#include "ComponentBase.h"

#include "SceneManager.h"
#include "DataContainer.h"
#include "GenericSubject.h"
#include "TransformComponent.h"

ComponentBase::ComponentBase()
	: m_vec_RefList{ nullptr }
	, m_bStarted{ false }
	, m_bActive{ true }
{
	m_bStarted = false;
}
ComponentBase::ComponentBase(ComponentBase& com)
{
	m_vec_RefList = nullptr;
}
ComponentBase::~ComponentBase()
{
	//DEFAULT_LOG("Default component destructor called. Ensure your concrete component's destructor is virtual.");
}
void ComponentBase::Init(std::vector<ComponentBase*>* refList)
{
	m_vec_RefList = refList;
}
//
void ComponentBase::Update(double dt)
{
	DEFAULT_LOG("Default update called.");
}
void ComponentBase::CheckStarted()
{
	if (!m_bStarted)
	{
		Start();
		m_bStarted = true;
	}
}
void ComponentBase::Start()
{
	return;
}

bool ComponentBase::IsActive()
{
	return m_bActive;
}
void ComponentBase::SetActive(bool b)
{
	m_bActive = b;
}
bool ComponentBase::IsStarted()
{
	return m_bStarted;
}
void ComponentBase::SetStarted(bool b)
{
	m_bStarted = b;
}
void ComponentBase::Notify(ComponentBase* com, std::string msg)
{
	GenericSubject::GetInstance()->NotifySubject(com, msg);
}