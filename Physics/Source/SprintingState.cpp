#include "SprintingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"

SprintingState::SprintingState()
{
}

SprintingState::~SprintingState()
{
}

PlayerState* SprintingState::HandleInput(ComponentBase* com, double dt)
{
	// TO BE IMPLEMENTED WHEN KEY TRIGGER IS ADDED
	return nullptr;
}
void SprintingState::OnEnter(ComponentBase* com)
{
}