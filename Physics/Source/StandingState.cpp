#include "StandingState.h"
#include "Application.h"
#include "CrouchingState.h"
#include "ChengPlayerScript.h"
StandingState::StandingState()
{
	m_fSprintMultiplier = 2.0f;
	m_fBaseMovementSpeed = 10;
}

StandingState::~StandingState()
{
}

PlayerState* StandingState::HandleInput(ComponentBase* com, double dt)
{
	// Sprint
	if (Application::IsKeyPressed(VK_SHIFT))
	{
		com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed * m_fSprintMultiplier);
	}
	else
	{
		com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed);
	}
	// Crouch
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		return new CrouchingState;
	}

	return nullptr;
}
void StandingState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, STANDING_HEIGHT, 0);
	com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed);
}