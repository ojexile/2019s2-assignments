#include "RangedState.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"
RangedState::RangedState()
{
}

RangedState::~RangedState()
{
}

State * RangedState::HandleState(ComponentBase * com)
{
	bool bInShootingRange = PlayerInRange(com, 10);
	if (bInShootingRange)
	{
		AI->SetTarget({});
		Vector3 Dir = DirToPlayer(com);
		DamagePlayer(0.1f, 1, Dir);
	}
	else if (PlayerInRange(com))
	{
		Vector3 Dir = DirToPlayer(com);
		AI->SetTarget(Dir);
	}
	else
		return &AIStatesList::Idle;
	return this;
}

void RangedState::OnEnter(ComponentBase * com)
{
	com->RENDER->SetColor(1, 0.2f, 0.1f);
}

void RangedState::OnExit(ComponentBase * com)
{
}