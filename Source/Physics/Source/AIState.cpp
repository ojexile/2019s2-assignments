#include "AIState.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "EntityScript.h"
#include "Rigidbody.h"

bool AIState::PlayerInRange(ComponentBase* com)
{
	GameObject* Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	if (!Player->GetComponent<EntityScript>()->GetCanDie())
		return false;
	Vector3 PlayerPos = Player->TRANS->GetPosition();
	Vector3 Pos = com->TRANS->GetPosition();
	if ((PlayerPos.y - Pos.y) > 5)
		return false;
	PlayerPos.y = 0;
	Pos.y = 0;
	float Range = Player->GetComponent<EntityScript>()->GetBaseStats()->GetDetectionRadius() +
		com->GetComponent<EntityScript>()->GetBaseStats()->GetDetectionRadius();
	if ((PlayerPos - Pos).Length() < Range)
		return true;
	return false;
}

bool AIState::PlayerInRange(ComponentBase * com, float dist)
{
	GameObject* Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	if (!Player->GetComponent<EntityScript>()->GetCanDie())
		return false;
	Vector3 PlayerPos = Player->TRANS->GetPosition();
	float Range = dist;
	if ((PlayerPos - com->TRANS->GetPosition()).Length() < Range)
		return true;
	return false;
}

Vector3 AIState::DirToPlayer(ComponentBase * com)
{
	GameObject* Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	Vector3 Dir = Player->TRANS->GetPosition() - com->TRANS->GetPosition();
	return Dir;
}

void AIState::DamagePlayer(int damage, float force, Vector3 Dir)
{
	GameObject* Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	Player->GetComponent<EntityScript>()->Damage(damage);
	Player->GetComponent<Rigidbody>()->AddForce(Dir * force);
}

AIState::AIState()
{
}

AIState::~AIState()
{
}