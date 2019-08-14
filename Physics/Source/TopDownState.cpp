#include "TopDownState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "StandingState.h"

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
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->SetRelativePosition(Vector3{ 0,1,0 } * 100);
	SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir({ 0, -1, 0});
	com->GetComponent<PlayerScript>()->SetMovementSpeed(0, 0);
}