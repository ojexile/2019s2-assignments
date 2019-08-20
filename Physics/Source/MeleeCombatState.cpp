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
	com->RENDER->SetColor(1, 0.5f, 0);
	Vector3 Dir = DirToPlayer(com);
	com->GetComponent<AIEntityScript>()->SetTarget(Dir);

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

void MeleeCombatState::OnEnter(ComponentBase * com)
{
}

void MeleeCombatState::OnExit(ComponentBase * com)
{
}