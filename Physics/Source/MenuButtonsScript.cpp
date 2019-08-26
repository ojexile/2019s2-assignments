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
	m_fQuitFadeVal = 0.5f;
	m_fTutorialFadeVal = 0.5f;
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
	if (m_TutorialButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
		{
		}
		m_fTutorialFadeVal += UpRate + DownRate;
	}
	if (m_QuitButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
			Application::bExit = true;
		m_fQuitFadeVal += UpRate + DownRate;
	}

	m_PlayText->RENDER->SetAlpha(m_fPlayFadeVal);
	if (m_fPlayFadeVal > Default)
		m_fPlayFadeVal -= DownRate;
	m_fPlayFadeVal = Math::Clamp(m_fPlayFadeVal, 0.f, 1.2f);

	m_TutorialText->RENDER->SetAlpha(m_fTutorialFadeVal);
	if (m_fTutorialFadeVal > Default)
		m_fTutorialFadeVal -= DownRate;
	m_fTutorialFadeVal = Math::Clamp(m_fTutorialFadeVal, 0.f, 1.2f);

	m_QuitText->RENDER->SetAlpha(m_fQuitFadeVal);
	if (m_fQuitFadeVal > Default)
		m_fQuitFadeVal -= DownRate;
	m_fQuitFadeVal = Math::Clamp(m_fQuitFadeVal, 0.f, 1.2f);
}