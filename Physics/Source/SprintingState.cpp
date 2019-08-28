#include "SprintingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"
#include "PlayerStatsScript.h"
#include "TopDownState.h"
#include "CameraScript.h"
#include "Time.h"
#include "StandingState.h"
#include "Engine.h"
#include "PlayerStateList.h"
#define INFINITE true
SprintingState::SprintingState()
{
}

SprintingState::~SprintingState()
{
}

State* SprintingState::HandleState(ComponentBase* com)
{
	float dt = Time::GetInstance()->GetDeltaTimeF();
	float fDrain;
	if (INFINITE)
		fDrain = 0.f;
	else
		fDrain = 20 * (float)dt;
	com->GetComponent<EntityScript>()->GetValues()->OffsetStamina(fDrain);
	// Sprint
	if (!InputManager::GetInstance()->GetInputStrength("PlayerSprint"))
	{
		return  &PlayerStateList::Standing;
	}
	// Top Down
	if (InputManager::GetInstance()->GetInputStrength("SwitchCam"))
	{
		return  &PlayerStateList::TopDown;
	}
	if (com->GetComponent<PlayerScript>()->GetValues()->GetStamina() < fDrain)
	{
		return  &PlayerStateList::Standing;
	}
	m_MovementCommand.HandleCommand(com);

	return nullptr;
}
void SprintingState::OnEnter(ComponentBase* com)
{
	CameraScript::SetTopDown(false);
	if (INFINITE)
		com->GetComponent<EntityScript>()->GetAdditionalStats()->SetMovement(800, 500);
	else
		com->GetComponent<EntityScript>()->GetAdditionalStats()->SetMovement(100, 50);
}

void SprintingState::OnExit(ComponentBase * com)
{
}