#include "StandingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"

StandingState::StandingState()
{
	m_fBaseAccel = 300;
	m_fSprintMultiplier = 4.0f;
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
		com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed * m_fSprintMultiplier, m_fBaseAccel * m_fSprintMultiplier);
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
		// Add force in direction of reticle
		Vector3 vTempDir = { 0,0,-1 };
		com->RIGID->AddForce(vTempDir * m_fDodgeForce);
		bDodge = true;
	}
	// Jump
	// TODO: 

	//SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetRelativePosition(Vector3{ 100,100,100 });
	return nullptr;
}
void StandingState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetRelativePosition(Vector3{ 1,1,1 } * 100);
	com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
}