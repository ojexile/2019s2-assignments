#include "LoginScript.h"
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "PlayerData.h"
#include "MainMenu.h"
#include "UIButtonComponent.h"
LoginScript::LoginScript(GameObject * u, GameObject * p, GameObject* uq, GameObject* pq)
{
	User = u;
	Pass = p;
	UserQ = uq;
	PassQ = pq;
	m_bTriggered = false;
	Selected = u;
}

LoginScript::~LoginScript()
{
}

void LoginScript::Start()
{
	SetSelected(LoginScript::eUSER);
}

void LoginScript::Update(double dt)
{
	if (Application::Key == ' ')
		m_bTriggered = false;
	else if (!m_bTriggered)
	{
		Selected->RENDER->AddText(toupper(Application::Key));
	}
	if (InputManager::GetInstance()->GetInputStrength("Back"))
	{
		Selected->RENDER->RemoveText();
	}
	if (InputManager::GetInstance()->GetInputStrength("Enter"))
	{
		if (Selected == Pass)
		{
			LoginLocal();
		}
	}

	if (InputManager::GetInstance()->GetInputStrength("Tab"))
	{
		if (Selected == User)
		{
			SetSelected(LoginScript::ePASS);
		}
		else
		{
			SetSelected(LoginScript::eUSER);
		}
	}
	if (InputManager::GetInstance()->GetInputStrength("Click"))
	{
		if (UserQ->GC(UIButtonComponent)->GetHover())
		{
			SetSelected(LoginScript::eUSER);
		}
		else if (PassQ->GC(UIButtonComponent)->GetHover())
		{
			SetSelected(LoginScript::ePASS);
		}
	}
}

void LoginScript::SetSelected(eSelectedSpace e)
{
	switch (e)
	{
	case LoginScript::eUSER:
		Selected = User;
		PassQ->RENDER->SetAlpha(1.f);
		PassQ->RENDER->SetColor(.2f);

		UserQ->RENDER->SetAlpha(.5f);
		UserQ->RENDER->SetColor(.1f);
		break;
	case LoginScript::ePASS:
		Selected = Pass;
		UserQ->RENDER->SetAlpha(1.f);
		UserQ->RENDER->SetColor(.2f);

		PassQ->RENDER->SetAlpha(.5f);
		PassQ->RENDER->SetColor(.1f);
		break;
	default:
		break;
	}
}

void LoginScript::LoginLocal()
{
	std::string sUser = User->RENDER->GetText();
	std::string sPass = Pass->RENDER->GetText();
	if (PlayerData::GetInstance()->Load(sUser, sPass))
	{
		SceneManager::GetInstance()->ChangeScene(new MainMenu);
	}
	else
	{
	}
}

void LoginScript::CreateLocal()
{
	std::string sUser = User->RENDER->GetText();
	std::string sPass = Pass->RENDER->GetText();
	if (sUser == "" || sPass == "")
		return;
	if (PlayerData::GetInstance()->Create(sUser, sPass))
	{
		LoginLocal();
	}
	else
	{
	}
}