#include "ComponentBase.h"

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