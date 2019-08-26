#include "MenuButtonsScript.h"
#include "UIButtonComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DefaultScene.h"
#include "Application.h"

MenuButtonsScript::MenuButtonsScript(GameObject* PlayText, GameObject* PlayButt,
	GameObject* QuitText, GameObject* QuitButt)
	: m_PlayText(PlayText)
	, m_PlayButt(PlayButt)
	, m_QuitText(QuitText)
	, m_QuitButt(QuitButt)
{
}

MenuButtonsScript::~MenuButtonsScript()
{
}

void MenuButtonsScript::Update(double dt)
{
	if (m_PlayButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
			SceneManager::GetInstance()->ChangeScene(new DefaultScene);
	}
	if (m_QuitButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
			Application::bExit = true;
	}
}