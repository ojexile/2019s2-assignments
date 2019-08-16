#include "TopDownState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "StandingState.h"
#include "CameraScript.h"
TopDownState::TopDownState()
{
}

TopDownState::~TopDownState()
{
}

PlayerState* TopDownState::HandleInput(ComponentBase* com, double dt)
{
	if (!InputManager::GetInstance()->GetInputStrength("SwitchCam"))
	{
		return new StandingState;
	}
	return nullptr;
}
void TopDownState::OnEnter(ComponentBase* com)
{
	// SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetPosition(0, 20, 0);
	CameraScript::SetTopDown(true);
	// com->GetComponent<PlayerScript>()->SetMovementSpeed(0, 0);
}