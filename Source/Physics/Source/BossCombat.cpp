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
		float meleeRange = 7;

		if (PlayerInRange(com, meleeRange))
		{
			if (!Math::RandIntMinMax(0, 2))
				return &AIStatesList::ShockWave;
			else
				DamagePlayer(20, 400, Dir);
		}
	}
	else
		return com->GetComponent<EntityScript>()->GetBehaviour()->GetIdleState();
	return this;
}

void BossCombat::OnEnter(ComponentBase * com)
{
	GameObject* ret = dynamic_cast<Component*>(com)->GetChild(0);
	if (ret)
		ret->RENDER->SetColor(1, 0.5f, 0);
	Vector3 Dir = DirToPlayer(com);
	AI->SetTarget(Dir);
}

void BossCombat::OnExit(ComponentBase * com)
{
}