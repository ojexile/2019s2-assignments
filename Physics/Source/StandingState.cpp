#include "StandingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "PlayerStatsScript.h"
#include "TopDownState.h"
#include "CameraScript.h"
#include "Time.h"
#include "SprintingState.h"
#include "PlayerStateList.h"
StandingState::StandingState()
{
	m_fMovementBoost = 50;
	m_fForrceBoost = 20;
}

StandingState::~StandingState()
{
}

State* StandingState::HandleState(ComponentBase* com)
{
	float dt = Time::GetInstance()->GetDeltaTimeF();

	// Sprint
	if (InputManager::GetInstance()->GetInputStrength("PlayerSprint") && com->GetComponent<PlayerScript>()->GetValues()->GetStamina() >= 25.f)
	{
		return &PlayerStateList::Sprinting;
	}
	// Dodge
	if (InputManager::GetInstance()->GetInputStrength("PlayerDodge"))
	{
		float fDrain = 25;
		if (com->GetComponent<PlayerScript>()->GetValues()->GetStamina() >= fDrain)
		{
			com->GetComponent<PlayerScript>()->Dash();
			com->GetComponent<EntityScript>()->GetValues()->OffsetStamina(fDrain);
		}
	}
	// Top Down
	if (InputManager::GetInstance()->GetInputStrength("SwitchCam"))
	{
		return  &PlayerStateList::TopDown;
	}
	m_MovementCommand.HandleCommand(com);

	return nullptr;
}
void StandingState::OnEnter(ComponentBase* com)
{
	CameraScript::SetTopDown(false);
	com->GetComponent<EntityScript>()->GetAdditionalStats()->SetMovement(0, 0);
}

void StandingState::OnExit(ComponentBase * com)
{
}