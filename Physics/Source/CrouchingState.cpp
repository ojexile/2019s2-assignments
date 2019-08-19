#include "CrouchingState.h"
#include "Application.h"
#include "StandingState.h"
#include "PlayerScript.h"

#include "InputManager.h"
#define CROUCHING_HEIGHT 7.3f
CrouchingState::CrouchingState()
{
	m_fBaseMovementSpeed = 3.9f;
	m_fTimer = 0;
}

CrouchingState::~CrouchingState()
{
}
State* CrouchingState::HandleState(ComponentBase* com)
{
	// Crouch
	static bool bCrouch = true;
	if (!InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	{
		bCrouch = false;
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerCrouch") && !bCrouch)
	{
		return new StandingState;
	}
	// SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, CROUCHING_HEIGHT, 0);
	return nullptr;
}
void CrouchingState::OnEnter(ComponentBase* com)
{
	// SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, CROUCHING_HEIGHT, 0);
	com->GetComponent<PlayerScript>()->GetAdditionalStats()->SetMovement(m_fBaseMovementSpeed, 200);
}

void CrouchingState::OnExit(ComponentBase * com)
{
}
