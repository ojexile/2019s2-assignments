#include "MenuButtonsScript.h"
#include "UIButtonComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DefaultScene.h"
#include "Application.h"

MenuButtonsScript::MenuButtonsScript(GameObject* PlayText, GameObject* PlayButt,
	GameObject* QuitText, GameObject* QuitButt,
	GameObject* TutorialText, GameObject* TutorialButt)
	: m_PlayText(PlayText)
	, m_PlayButt(PlayButt)
	, m_QuitText(QuitText)
	, m_QuitButt(QuitButt)
	, m_TutorialText(TutorialText)
	, m_TutorialButt(TutorialButt)
{
	m_fPlayFadeVal = 0.5f;
}

MenuButtonsScript::~MenuButtonsScript()
{
}

void MenuButtonsScript::Update(double dt)
{
	float UpRate = (float)dt * 1.04f;
	float DownRate = (float)dt * 1.04f;
	float Default = 0.8f;
	if (m_PlayButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
			SceneManager::GetInstance()->ChangeScene(new DefaultScene);
		m_fPlayFadeVal += UpRate + DownRate;
	}
	if (m_QuitButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
			Application::bExit = true;
	}

	m_PlayText->RENDER->SetAlpha(m_fPlayFadeVal);
	if (m_fPlayFadeVal > Default)
		m_fPlayFadeVal -= DownRate;
	m_fPlayFadeVal = Math::Clamp(m_fPlayFadeVal, 0.f, 1.2f);
}