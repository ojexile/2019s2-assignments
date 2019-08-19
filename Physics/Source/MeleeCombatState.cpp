#include "MeleeCombatState.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
MeleeCombatState::MeleeCombatState()
{
}

MeleeCombatState::~MeleeCombatState()
{
}

State * MeleeCombatState::HandleState(ComponentBase * com)
{
	Vector3 Dir = DirToPlayer(com);
	com->GetComponent<EntityScript>()->RotateTowards(Dir);
	com->GetComponent<EntityScript>()->MoveForwards();
	float meleeRange = 2;
	if (PlayerInRange(com, meleeRange))
	{
		DamagePlayer(5, 300, Dir);
	}
	CHENG_LOG("Melee");
	return this;
}

void MeleeCombatState::OnEnter(ComponentBase * com)
{
}

void MeleeCombatState::OnExit(ComponentBase * com)
{
}