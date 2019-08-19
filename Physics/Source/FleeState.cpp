#include "FleeState.h"
#include "EntityScript.h"
#include "IdleState.h"

FleeState::FleeState(State* Combat)
	:AIState(Combat)
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
		return new IdleState(this);
	return this;
}

void FleeState::OnEnter(ComponentBase * com)
{
}

void FleeState::OnExit(ComponentBase * com)
{
}