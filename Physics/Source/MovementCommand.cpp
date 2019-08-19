#include "MovementCommand.h"
#include "InputManager.h"
#include "EntityScript.h"
#include "CameraScript.h"


MovementCommand::MovementCommand()
{
}


MovementCommand::~MovementCommand()
{
}

void MovementCommand::HandleCommand(ComponentBase * com)
{
	// Movement
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") > 0)
	{
		com->GetComponent<EntityScript>()->Move(CameraScript::GetFront());
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") < 0)
	{
		com->GetComponent<EntityScript>()->Move(-CameraScript::GetFront());
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") < 0)
	{
		com->GetComponent<EntityScript>()->Move(-CameraScript::GetRight());
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") > 0)
	{
		com->GetComponent<EntityScript>()->Move(CameraScript::GetRight());
	}

	if (InputManager::GetInstance()->GetInputStrength("PlayerJump") != 0)
	{
		com->GetComponent<EntityScript>()->Jump();
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerInteract") != 0)
	{
		com->Notify(com, "Interact");
	}
}
