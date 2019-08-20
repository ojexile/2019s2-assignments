#include "MeleeCombatState.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"
MeleeCombatState::MeleeCombatState()
{
}

MeleeCombatState::~MeleeCombatState()
{
}

State * MeleeCombatState::HandleState(ComponentBase * com)
{
	if (PlayerInRange(com))
	{
		Vector3 Dir = DirToPlayer(com);
		AI->SetTarget(Dir);
		float meleeRange = 3;
		if (PlayerInRange(com, meleeRange))
		{
			DamagePlayer(5, 300, Dir);
		}
	}
	else
		return &AIStatesList::Idle;
	com->RENDER->SetColor(1, 0.5f, 0);
	return this;
}

void MeleeCombatState::OnEnter(ComponentBase * com)
{
	Vector3 Dir = DirToPlayer(com);
	AI->SetTarget(Dir);
}

void MeleeCombatState::OnExit(ComponentBase * com)
{
}