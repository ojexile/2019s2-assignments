#include "ComponentBase.h"
#include "SceneManager.h"
#include "DataContainer.h"
ComponentBase::ComponentBase()
{
	m_vec_RefList = nullptr;
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