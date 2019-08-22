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
			DamagePlayer(5, 300, Dir);
		}
	}
	else
		return &AIStatesList::Idle;
	return this;
}

void FleeState::OnEnter(ComponentBase * com)
{
	GameObject* ret = dynamic_cast<Component*>(com)->GetChild(0);
	if (ret)
		ret->RENDER->SetColor(0, 0.5f, 1);
}

void FleeState::OnExit(ComponentBase * com)
{
}