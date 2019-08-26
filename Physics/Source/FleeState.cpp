#include "FleeState.h"
#include "EntityScript.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

FleeState::FleeState()
{
}

FleeState::~FleeState()
{
}

State * FleeState::HandleState(ComponentBase * com)
{
	Vector3 Dir = DirToPlayer(com);
	AI->SetTarget(-Dir);
	if (PlayerInRange(com))
	{
		float meleeRange = 2;
		if (PlayerInRange(com, meleeRange))
		{
			DamagePlayer(2, 300, Dir);
		}
	}
	else
		return com->GetComponent<EntityScript>()->GetBehaviour()->GetIdleState();
	return this;
}

void FleeState::OnEnter(ComponentBase * com)
{
	GameObject* ret = dynamic_cast<Component*>(com)->GetChild(0);
	if (ret)
		ret->RENDER->SetColor(0, 1.f, 0.4f);
}

void FleeState::OnExit(ComponentBase * com)
{
}