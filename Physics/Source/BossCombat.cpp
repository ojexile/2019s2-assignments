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

BossCombat::BossCombat(GameObject* ShockWave)
	:m_ShockWave(ShockWave)
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
			DamagePlayer(0, 600, Dir);
			GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
			GameObject* go = GOM->AddGameObject(m_ShockWave);
			go->TRANS->SetPosition(com->TRANS->GetPosition());
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