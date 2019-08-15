#include "StandingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "StaminaScript.h"
#include "TopDownState.h"

StandingState::StandingState()
{
	m_fBaseAccel = 300;
	m_fSprintMultiplier = 2.0f;
	m_fBaseMovementSpeed = 40;

	m_fDodgeForce = 4000;
}

StandingState::~StandingState()
{
}

PlayerState* StandingState::HandleInput(ComponentBase* com, double dt)
{
	// Sprint
	if (InputManager::GetInstance()->GetInputStrength("PlayerSprint"))
	{
		float fDrain = 100;
		if (com->GetComponent<StaminaScript>()->GetStamina() >= dt * fDrain)
		{
			com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed * m_fSprintMultiplier, m_fBaseAccel * m_fSprintMultiplier);
			com->GetComponent<StaminaScript>()->DrainStamina(dt * fDrain);
		}
	}
	// Crouch
	if (InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	{
		// return new CrouchingState; /// Disabled until key trigger is added
		com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed / m_fSprintMultiplier, m_fBaseAccel / m_fSprintMultiplier);
	}
	if (!InputManager::GetInstance()->GetInputStrength("PlayerSprint") && !InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	{
		com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
	}
	// Dodge
	static bool bDodge = false;

	if (!InputManager::GetInstance()->GetInputStrength("PlayerDodge"))
	{
		bDodge = false;
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerDodge") && !bDodge)
	{
		float fDrain = 25;
		if (com->GetComponent<StaminaScript>()->GetStamina() >= fDrain)
		{
			// Add force in direction of reticle
			com->GetComponent<PlayerScript>()->Dash();
			bDodge = true;
			com->GetComponent<StaminaScript>()->DrainStamina(fDrain);
		}
	}
	// Top Down
	if (InputManager::GetInstance()->GetInputStrength("SwitchCam"))
	{
		return new TopDownState;
	}
	// Jump
	// TODO:

	//SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetRelativePosition(Vector3{ 100,100,100 });
	return nullptr;
}
void StandingState::OnEnter(ComponentBase* com)
{
	// SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetRelativePosition(Vector3{ 1,1,1 } * 100);
	// SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir({-1, -1, -1});
	com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
}