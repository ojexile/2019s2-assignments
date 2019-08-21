#include "BossCombat.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"
BossCombat::BossCombat()
{
}

BossCombat::~BossCombat()
{
}

State * BossCombat::HandleState(ComponentBase * com)
{
	if (PlayerInRange(com))
	{
		Vector3 Dir = DirToPlayer(com);
		AI->SetTarget(Dir);
		float meleeRange = 4;
		if (PlayerInRange(com, meleeRange))
		{
			// Create shockwave effect
		}
	}
	else
		return &AIStatesList::Idle;
	com->RENDER->SetColor(1, 0.5f, 0);
	return this;
}

void BossCombat::OnEnter(ComponentBase * com)
{
	Vector3 Dir = DirToPlayer(com);
	AI->SetTarget(Dir);
}

void BossCombat::OnExit(ComponentBase * com)
{
}