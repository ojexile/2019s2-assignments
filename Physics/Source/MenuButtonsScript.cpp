#include "MenuButtonsScript.h"
#include "UIButtonComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DefaultScene.h"

MenuButtonsScript::MenuButtonsScript(GameObject * PlayText, GameObject * PlayButt)
	: m_PlayText(PlayText)
	, m_PlayButt(PlayButt)
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
}