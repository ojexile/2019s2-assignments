#include "WanderState.h"
#include "EntityScript.h"
#include "IdleState.h"
#include "SceneManager.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

#define MIN_TIME 1
#define MAX_TIME 2

WanderState::WanderState()
{
	m_fTime = 0;
}

WanderState::~WanderState()
{
}

State * WanderState::HandleState(ComponentBase * com)
{
	com->RENDER->SetColor(0, 0.5f, 1);
	// Check for player
	if (PlayerInRange(com))
	{
		return com->GetComponent<AIEntityScript>()->GetCombatState();
	}
	if (m_SW.Stop()->GetTime() < m_fTime)
	{
		return this;
	}
	else
		return &AIStatesList::Idle;
}

void WanderState::OnEnter(ComponentBase * com)
{
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(MIN_TIME, MAX_TIME);
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
	com->GetComponent<AIEntityScript>()->SetTarget({0,0,0});
}