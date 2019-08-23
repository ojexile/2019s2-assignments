#include "SprintingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "PlayerStatsScript.h"
#include "TopDownState.h"
#include "CameraScript.h"
#include "Time.h"
#include "StandingState.h"
SprintingState::SprintingState()
{
}

SprintingState::~SprintingState()
{
}

State* SprintingState::HandleState(ComponentBase* com)
{
	float dt = Time::GetInstance()->GetDeltaTimeF();
	com->GetComponent<EntityScript>()->GetValues()->OffsetStamina(60 * dt);
	// Sprint
	if (!InputManager::GetInstance()->GetInputStrength("PlayerSprint"))
	{
		return new StandingState;
	}
	//// Crouch
	//if (InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	//{
	//	// com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(m_fBaseMovementSpeed / m_fSprintMultiplier, m_fBaseAccel / m_fSprintMultiplier);
	//}
	//if (!InputManager::GetInstance()->GetInputStrength("PlayerSprint") && !InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	//{
	//	com->GetComponent<EntityScript>()->GetAdditionalStats()->SetMovement(0, 0);
	//}
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
		return new TopDownState;
	}

	m_MovementCommand.HandleCommand(com);

	return nullptr;
}
void SprintingState::OnEnter(ComponentBase* com)
{
	CameraScript::SetTopDown(false);
	com->GetComponent<EntityScript>()->GetAdditionalStats()->SetMovement(50, 20);
}

void SprintingState::OnExit(ComponentBase * com)
{
}