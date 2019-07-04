#include "ComponentBase.h"
#include "SceneManager.h"
#include "DataContainer.h"
ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::Init(std::vector<ComponentBase*>* refList)
{
	m_vec_RefList = refList;
}
void ComponentBase::Update(double dt)
{
	DEFAULT_LOG("Default update called.");
}