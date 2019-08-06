#include "ProneState.h"
#include "Application.h"
#include "StandingState.h"
#include "ChengPlayerScript.h"
#include "KeyboardManager.h"
#define PRONT_HEIGHT 3.f
ProneState::ProneState()
{
	m_fBaseMovementSpeed = 0.4f;
}

ProneState::~ProneState()
{
}
PlayerState* ProneState::HandleInput(ComponentBase* com, double dt)
{
	// Crouch
	if (KeyboardManager::GetInstance()->GetKeyTriggered("Crouch"))
	{
		return new StandingState;
	}
	return nullptr;
}
void ProneState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, PRONT_HEIGHT, 0);
	com->GetComponent<ChengPlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, 200);
}