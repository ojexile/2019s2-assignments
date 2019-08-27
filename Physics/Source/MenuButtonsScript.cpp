#include "MenuButtonsScript.h"
#include "UIButtonComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DefaultScene.h"
#include "Application.h"
#include "PlayerData.h"

#include "AbilityGrenade.h"
#include "AbilityDash.h"
#include "AbilityHeal.h"
#include "AbilitySlowTime.h"

MenuButtonsScript::MenuButtonsScript(GameObject * PlayText, GameObject * PlayButt, GameObject * QuitText, GameObject * QuitButt, GameObject * TutorialText, GameObject * TutorialButt, GameObject * TutorialBox, GameObject * Ability0, GameObject * Ability1, GameObject * Ability2, GameObject * Ability3)
	: m_PlayText(PlayText)
	, m_PlayButt(PlayButt)
	, m_QuitText(QuitText)
	, m_QuitButt(QuitButt)
	, m_TutorialText(TutorialText)
	, m_TutorialButt(TutorialButt)
	, m_TutorialBox(TutorialBox)
	, m_Ability0(Ability0)
	, m_Ability1(Ability1)
	, m_Ability2(Ability2)
	, m_Ability3(Ability3)
{
	m_fPlayFadeVal = 0.5f;
	m_fQuitFadeVal = 0.5f;
	m_fTutorialFadeVal = 0.5f;
}

void MenuButtonsScript::Start()
{
	if (!PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eGRENADE))
	{
		m_Ability1->RENDER->SetColor(0.2f);
	}
	if (!PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eHEAL))
	{
		m_Ability2->RENDER->SetColor(0.2f);
	}
	if (!PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eSLOW_TIME))
	{
		m_Ability3->RENDER->SetColor(0.2f);
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
	bool bClick = InputManager::GetInstance()->GetInputStrength("Click");
	if (m_PlayButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (bClick)
		{
			m_Ability0->SetActive(!m_Ability0->IsActive());
			m_Ability1->SetActive(!m_Ability1->IsActive());
			m_Ability2->SetActive(!m_Ability2->IsActive());
			m_Ability3->SetActive(!m_Ability3->IsActive());
		}
		m_fPlayFadeVal += UpRate + DownRate;
	}
	if (m_TutorialButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (bClick)
		{
			m_TutorialBox->SetActive(!m_TutorialBox->IsActive());
		}
		m_fTutorialFadeVal += UpRate + DownRate;
	}
	if (m_QuitButt->GetComponent<UIButtonComponent>()->GetHover())
	{
		if (bClick)
			Application::bExit = true;
		m_fQuitFadeVal += UpRate + DownRate;
	}
	// Ability Selection--------------------------------------------------------------------------------
	if (m_Ability0->IsActive())
	{
		if (m_Ability0->GC(UIButtonComponent)->GetHover())
		{
			if (bClick)
			{
				if (PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eDASH))
				{
					// Set active ability
					PlayerData::GetInstance()->SetAbility(new AbilityDash(5, 75), PlayerData::eDASH);
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
			if (bClick)
			{
				if (PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eGRENADE))
				{
					// Set active ability
					PlayerData::GetInstance()->SetAbility(new AbilityGrenade(5, 90), PlayerData::eGRENADE);
					// Change scene
					SceneManager::GetInstance()->ChangeScene(new DefaultScene());
				}
				// Purchase
				else
				{
					if (PlayerData::GetInstance()->GetCoins() >= 3)
					{
						PlayerData::GetInstance()->OffsetCoins(-3);
						PlayerData::GetInstance()->ActivateAbility(PlayerData::eGRENADE);
						m_Ability1->RENDER->ResetColor();
						PlayerData::GetInstance()->Save();
					}
				}
			}
		}
	}
	if (m_Ability2->IsActive())
	{
		if (m_Ability2->GC(UIButtonComponent)->GetHover())
		{
			if (bClick)
			{
				if (PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eHEAL))
				{
					// Set active ability
					PlayerData::GetInstance()->SetAbility(new AbilityHeal(3, 5, 90), PlayerData::eHEAL);
					// Change scene
					SceneManager::GetInstance()->ChangeScene(new DefaultScene());
				}
				// Purchase
				else
				{
					if (PlayerData::GetInstance()->GetCoins() >= 3)
					{
						PlayerData::GetInstance()->OffsetCoins(-3);
						PlayerData::GetInstance()->ActivateAbility(PlayerData::eHEAL);
						m_Ability2->RENDER->ResetColor();
						PlayerData::GetInstance()->Save();
					}
				}
			}
		}
	}
	if (m_Ability3->IsActive())
	{
		if (m_Ability3->GC(UIButtonComponent)->GetHover())
		{
			if (bClick)
			{
				if (PlayerData::GetInstance()->GetAbilityActivated(PlayerData::eSLOW_TIME))
				{
					// Set active ability
					PlayerData::GetInstance()->SetAbility(new AbilitySlowTime(3, 5, 90), PlayerData::eSLOW_TIME);
					// Change scene
					SceneManager::GetInstance()->ChangeScene(new DefaultScene());
				}
				// Purchase
				else
				{
					if (PlayerData::GetInstance()->GetCoins() >= 3)
					{
						PlayerData::GetInstance()->OffsetCoins(-3);
						PlayerData::GetInstance()->ActivateAbility(PlayerData::eSLOW_TIME);
						m_Ability3->RENDER->ResetColor();
						PlayerData::GetInstance()->Save();
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