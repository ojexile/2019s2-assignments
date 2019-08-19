#include "MeleeCombatState.h"
#include "EntityScript.h"
#include "SceneManager.h"

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
	// com->GetComponent<EntityScript>()->Move(Dir);
	CHENG_LOG("Melee");
	return this;
}

void MeleeCombatState::OnEnter(ComponentBase * com)
{
}

void MeleeCombatState::OnExit(ComponentBase * com)
{
}
