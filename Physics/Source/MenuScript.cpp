#include "MenuScript.h"
#include "KeyboardManager.h"
#include "RojakAssignmentScene.h"
#include "SceneManager.h"
#include "Application.h"
MenuScript::MenuScript()
{
}

MenuScript::~MenuScript()
{
}
void MenuScript::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE) || Application::IsKeyPressed(VK_RETURN))
	{
		SceneManager::GetInstance()->ChangeScene(new RojakAssignmentScene);
	}
}