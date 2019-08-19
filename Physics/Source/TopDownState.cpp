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

State* TopDownState::HandleState(ComponentBase* com)
{
	if (!InputManager::GetInstance()->GetInputStrength("SwitchCam"))
	{
		return new StandingState;
	}
	return nullptr;
}
void TopDownState::OnEnter(ComponentBase* com)
{
	CameraScript::SetTopDown(true);
}
void TopDownState::OnExit(ComponentBase * com)
{
}
