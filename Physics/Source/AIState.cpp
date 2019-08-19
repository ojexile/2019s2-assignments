#include "AIState.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "EntityScript.h"
#include "Rigidbody.h"

bool AIState::PlayerInRange(ComponentBase* com)
{
	GameObject* Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	Vector3 PlayerPos = Player->TRANS->GetPosition();
	float Range = Player->GetComponent<EntityScript>()->GetBaseStats()->GetDetectionRadius() +
		com->GetComponent<EntityScript>()->GetBaseStats()->GetDetectionRadius();
	if ((PlayerPos - com->TRANS->GetPosition()).Length() < Range)
		return true;
	return false;
}

bool AIState::PlayerInRange(ComponentBase * com, float dist)
{
	GameObject* Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	Vector3 PlayerPos = Player->TRANS->GetPosition();
	float Range = 2;
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
	Player->GetComponent<EntityScript>()->Damage(10);
	Player->GetComponent<Rigidbody>()->AddForce(Dir * 500);
}

AIState::AIState(State* Combat)
	:m_Combat(Combat)
{
}

AIState::~AIState()
{
}