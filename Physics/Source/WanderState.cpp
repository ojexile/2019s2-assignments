#include "WanderState.h"
#include "EntityScript.h"
#include "IdleState.h"
#include "SceneManager.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

WanderState::WanderState(AIState* idle, float min, float max)
{
	m_fTime = 0;
	m_fMinTime = min;
	m_fMaxTime = max;
	m_Idle = idle;
}

WanderState::~WanderState()
{
}

State * WanderState::HandleState(ComponentBase * com)
{
	// Check for player
	if (PlayerInRange(com))
	{
		return com->GetComponent<AIEntityScript>()->GetBehaviour()->GetCombatState();
	}
	if (m_SW.Stop()->GetTime() < m_fTime)
	{
		return this;
	}
	else
		return com->GetComponent<AIEntityScript>()->GetBehaviour()->GetIdleState();
}

void WanderState::OnEnter(ComponentBase * com)
{
	GameObject* ret = dynamic_cast<Component*>(com)->GetChild(0);
	if (ret)
		ret->RENDER->SetColor(0, 0.5f, 1);
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(m_fMinTime, m_fMaxTime);
	m_vDir.SetZero();
	// Rand dir
	while (m_vDir.IsZero())
	{
		m_vDir.x = Math::RandFloatMinMax(-1, 1);
		m_vDir.z = Math::RandFloatMinMax(-1, 1);
	}
	m_vDir.Normalize();
	com->GetComponent<AIEntityScript>()->SetTarget(m_vDir);
}

void WanderState::OnExit(ComponentBase * com)
{
	com->GetComponent<AIEntityScript>()->SetTarget({ 0,0,0 });
}