#include "WanderState.h"
#include "EntityScript.h"


WanderState::WanderState()
{
}


WanderState::~WanderState()
{
}

State * WanderState::HandleState(ComponentBase * com)
{
	com->GetComponent<EntityScript>()->Move({ 1,0,0 });
	return nullptr;
}

void WanderState::OnEnter(ComponentBase * com)
{
}

void WanderState::OnExit(ComponentBase * com)
{
}
