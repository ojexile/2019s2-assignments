#include "CrouchingState.h"
#include "Application.h"
#include "StandingState.h"
#include "ChengPlayerScript.h"
CrouchingState::CrouchingState()
{
	m_fBaseMovementSpeed = 0.2f;
}

CrouchingState::~CrouchingState()
{
}
PlayerState* CrouchingState::HandleInput(ComponentBase* com, double dt)
{
	Vector3 vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	Vector3 vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = com->GetComponent<TransformComponent>();
	Vector3 vPlayerFront = vCameraFront;
	vPlayerFront.y = 0;
	Vector3 vRight = vCameraFront.Cross(vCameraUp);

	// Crouch
	if (!Application::IsKeyPressed(VK_LCONTROL))
	{
		return new StandingState;
	}
	return nullptr;
}
void CrouchingState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, CROUCHING_HEIGHT, 0);
	com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, 200);
}