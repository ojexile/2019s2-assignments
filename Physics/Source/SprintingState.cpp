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
SprintingState::SprintingState()
{
}

SprintingState::~SprintingState()
{
}

State* SprintingState::HandleState(ComponentBase* com)
{
	float dt = Time::GetInstance()->GetDeltaTimeF();
	com->GetComponent<EntityScript>()->GetValues()->OffsetStamina(20 * dt);
	// Sprint
	if (!InputManager::GetInstance()->GetInputStrength("PlayerSprint"))
	{
		return  &PlayerStateList::Standing;
	}
	// Dodge
	if (InputManager::GetInstance()->GetInputStrength("PlayerDodge"))
	{
		float fDrain = 25;
		if (com->GetComponent<PlayerScript>()->GetValues()->GetStamina() >= fDrain)
		{
			com->GetComponent<PlayerScript>()->Dash();
			com->GetComponent<EntityScript>()->GetValues()->OffsetStamina(fDrain);
		}
	}
	// Top Down
	if (InputManager::GetInstance()->GetInputStrength("SwitchCam"))
	{
		return  &PlayerStateList::TopDown;
	}

	m_MovementCommand.HandleCommand(com);

	return nullptr;
}
void SprintingState::OnEnter(ComponentBase* com)
{
	CameraScript::SetTopDown(false);
	com->GetComponent<EntityScript>()->GetAdditionalStats()->SetMovement(50, 20);
}

void SprintingState::OnExit(ComponentBase * com)
{
}