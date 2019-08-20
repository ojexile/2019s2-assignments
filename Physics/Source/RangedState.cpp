#include "RangedState.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "IdleState.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"
#include "WeaponScript.h"
#include "Time.h"
#include "GameObject.h"
void RangedState::FireGun(Component * com, const Vector3& vDir)
{
	GameObject* Gun = com->GetChild(0);
	WeaponScript* ws = Gun->GetComponent<WeaponScript>();
	ws->PullTrigger(vDir, Time::GetInstance()->GetDeltaTimeF());
	if (ws->GetMagazineRounds() <= 0)
		ws->ReloadWeapon();
}
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
		AI->RotateTowards(Dir);
		Component* comp = dynamic_cast<Component*>(com);
		FireGun(comp, Dir);
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