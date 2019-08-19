#include "FleeState.h"
#include "EntityScript.h"
#include "IdleState.h"
#include "AIStatesList.h"

FleeState::FleeState()
{
}

FleeState::~FleeState()
{
}

State * FleeState::HandleState(ComponentBase * com)
{
	Vector3 Dir = DirToPlayer(com);
	com->GetComponent<EntityScript>()->RotateTowards(-Dir);
	com->GetComponent<EntityScript>()->MoveForwards();
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