#include "MeleeCombatState.h"
#include "EntityScript.h"
#include "SceneManager.h"
#include "Rigidbody.h"
MeleeCombatState::MeleeCombatState()
{
}


MeleeCombatState::~MeleeCombatState()
{
}

State * MeleeCombatState::HandleState(ComponentBase * com)
{
	m_Player = SceneManager::GetInstance()->GetScene()->GetPlayer();
	Vector3 Dir = m_Player->TRANS->GetPosition() - com->TRANS->GetPosition();
	com->GetComponent<EntityScript>()->RotateTowards(Dir);
	com->GetComponent<EntityScript>()->MoveForwards();
	Vector3 PlayerPos = SceneManager::GetInstance()->GetScene()->GetPlayer()->TRANS->GetPosition();
	if ((PlayerPos - com->TRANS->GetPosition()).Length() < 3)
	{
		m_Player->GetComponent<EntityScript>()->Damage(10);
		m_Player->GetComponent<Rigidbody>()->AddForce(Dir * 500);
	}
	CHENG_LOG("Melee");
	return this;
}

void MeleeCombatState::OnEnter(ComponentBase * com)
{
}

void MeleeCombatState::OnExit(ComponentBase * com)
{
}
