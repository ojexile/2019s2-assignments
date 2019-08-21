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
	com->RENDER->SetColor(0.2f, 1.f, 0.2f);
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
}

void FleeState::OnExit(ComponentBase * com)
{
}