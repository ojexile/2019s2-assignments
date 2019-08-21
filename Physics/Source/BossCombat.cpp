#include "BossCombat.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "BlackholeScript.h"
#include <vector>

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
		float meleeRange = 5;

		if (PlayerInRange(com, meleeRange))
		{
			if (!Math::RandIntMinMax(0, 5))
				return &AIStatesList::ShockWave;
			else
				DamagePlayer(10, 1000, Dir);
		}
	}
	else
		return &AIStatesList::Idle;
	return this;
}

void BossCombat::OnEnter(ComponentBase * com)
{
	com->RENDER->SetColor(1, 0.5f, 0);
	Vector3 Dir = DirToPlayer(com);
	AI->SetTarget(Dir);
}

void BossCombat::OnExit(ComponentBase * com)
{
}