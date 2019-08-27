#include "MenuButtonsScript.h"
#include "UIButtonComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DefaultScene.h"
#include "Application.h"
#include "PlayerData.h"

#include "AbilityGrenade.h"
#include "AbilityDash.h"

MenuButtonsScript::MenuButtonsScript(GameObject* PlayText, GameObject* PlayButt,
	GameObject* QuitText, GameObject* QuitButt,
	GameObject* TutorialText, GameObject* TutorialButt,
	GameObject* TutorialBox, GameObject* Ability0, GameObject* Ability1)
	: m_PlayText(PlayText)
	, m_PlayButt(PlayButt)
	, m_QuitText(QuitText)
	, m_QuitButt(QuitButt)
	, m_TutorialText(TutorialText)
	, m_TutorialButt(TutorialButt)
	, m_TutorialBox(TutorialBox)
	, m_Ability0(Ability0)
	, m_Ability1(Ability1)
{
	m_fPlayFadeVal = 0.5f;
	m_fQuitFadeVal = 0.5f;
	m_fTutorialFadeVal = 0.5f;
}

void MenuButtonsScript::Start()
{
	if (!PlayerData::GetInstance()->GetGetAbilityActivated(PlayerData::eGRENADE))
	{
		m_Ability1->RENDER->SetColor(0.2f);
	}
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
		{
			m_Ability0->SetActive(!m_Ability0->IsActive());
			m_Ability1->SetActive(!m_Ability1->IsActive());
		}
		m_fPlayFadeVal += UpRate + DownRate;
	}
	if (m_TutorialButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
		{
			m_TutorialBox->SetActive(!m_TutorialBox->IsActive());
		}
		m_fTutorialFadeVal += UpRate + DownRate;
	}
	if (m_QuitButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (InputManager::GetInstance()->GetInputStrength("Click"))
			Application::bExit = true;
		m_fQuitFadeVal += UpRate + DownRate;
	}
	// Ability Selection--------------------------------------------------------------------------------
	if (m_Ability0->IsActive())
	{
		if (m_Ability0->GC(UIButtonComponent)->GetHover())
		{
			if (InputManager::GetInstance()->GetInputStrength("Click"))
			{
				if (PlayerData::GetInstance()->GetGetAbilityActivated(PlayerData::eDASH))
				{
					// Set active ability
					PlayerData::GetInstance()->SetAbility(new AbilityDash(1.5f, 60));
					// Change scene
					SceneManager::GetInstance()->ChangeScene(new DefaultScene());
				}
			}
		}
	}
	if (m_Ability1->IsActive())
	{
		if (m_Ability1->GC(UIButtonComponent)->GetHover())
		{
			if (InputManager::GetInstance()->GetInputStrength("Click"))
			{
				if (PlayerData::GetInstance()->GetGetAbilityActivated(PlayerData::eGRENADE))
				{
					// Set active ability
					PlayerData::GetInstance()->SetAbility(new AbilityGrenade(5, 50));
					// Change scene
					SceneManager::GetInstance()->ChangeScene(new DefaultScene());
				}
				// Purchase
				else
				{
					if (PlayerData::GetInstance()->GetCoins() > 3)
					{
						PlayerData::GetInstance()->OffsetCoins(-3);
						PlayerData::GetInstance()->ActivateAbility(PlayerData::eGRENADE);
						m_Ability1->RENDER->ResetColor();
					}
				}
			}
		}
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