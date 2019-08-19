#include "StandingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "PlayerStatsScript.h"
#include "TopDownState.h"
#include "CameraScript.h"
#include "Time.h"
StandingState::StandingState()
{
}

StandingState::~StandingState()
{
}

State* StandingState::HandleState(ComponentBase* com)
{
	float dt = Time::GetInstance()->GetDeltaTimeF();

	// Sprint
	if (InputManager::GetInstance()->GetInputStrength("PlayerSprint"))
	{
		float fDrain = 100;
		if (com->GetComponent<PlayerScript>()->GetValues()->GetStamina() >= dt * fDrain)
		{
			com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(m_fMovementBoost, m_fForrceBoost);
			com->GetComponent<PlayerScript>()->GetValues()->OffsetStamina(dt * fDrain);
		}
		else
		{
			com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(0, 0);
		}
	}
	// Crouch
	if (InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	{
		// com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(m_fBaseMovementSpeed / m_fSprintMultiplier, m_fBaseAccel / m_fSprintMultiplier);
	}
	if (!InputManager::GetInstance()->GetInputStrength("PlayerSprint") && !InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	{
		com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(0, 0);
	}
	// Dodge
	if (InputManager::GetInstance()->GetInputStrength("PlayerDodge"))
	{
		float fDrain = 25;
		if (com->GetComponent<PlayerScript>()->GetValues()->GetStamina() >= fDrain)
		{
			com->GetComponent<PlayerScript>()->Dash();
			com->GetComponent<PlayerScript>()->GetValues()->OffsetStamina(fDrain);
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
void StandingState::OnEnter(ComponentBase* com)
{
	// SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetPosition(0,100,0);
	CameraScript::SetTopDown(false);
	com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(0, 0);
}

void StandingState::OnExit(ComponentBase * com)
{
}
