#include "CrouchingState.h"
#include "Application.h"
#include "StandingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#define CROUCHING_HEIGHT 7.3f
CrouchingState::CrouchingState()
{
	m_fBaseMovementSpeed = 3.9f;
	m_fTimer = 0;
}

CrouchingState::~CrouchingState()
{
}
PlayerState* CrouchingState::HandleInput(ComponentBase* com, double dt)
{
	// Crouch
	if (KeyboardManager::GetInstance()->GetKeyTriggered("Crouch"))
	{
		return new StandingState;
	}

	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, CROUCHING_HEIGHT, 0);
	return nullptr;
}
void CrouchingState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, CROUCHING_HEIGHT, 0);
	com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, 200);
}