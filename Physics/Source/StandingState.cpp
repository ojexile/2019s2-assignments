#include "StandingState.h"
#include "Application.h"
#include "CrouchingState.h"
#include "ChengPlayerScript.h"
#include "KeyboardManager.h"
StandingState::StandingState()
{
	m_fBaseAccel = 300;
	m_fSprintMultiplier = 2.0f;
	m_fBaseMovementSpeed = 40;
}

StandingState::~StandingState()
{
}

PlayerState* StandingState::HandleInput(ComponentBase* com, double dt)
{
	// Sprint
	if (KeyboardManager::GetInstance()->GetKeyDown("Sprint"))
	{
		com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed * m_fSprintMultiplier, m_fBaseAccel * m_fSprintMultiplier);
	}
	else
	{
		com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
	}
	// Crouch
	if (KeyboardManager::GetInstance()->GetKeyTriggered("Crouch"))
	{
		return new CrouchingState;
	}

	return nullptr;
}
void StandingState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, STANDING_HEIGHT, 0);
	com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
}