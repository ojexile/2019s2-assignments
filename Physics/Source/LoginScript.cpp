#include "LoginScript.h"
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "PlayerData.h"
#include "MainMenu.h"
LoginScript::LoginScript(GameObject * u, GameObject * p)
{
	User = u;
	Pass = p;
	m_bTriggered = false;
	Selected = u;
}

LoginScript::~LoginScript()
{
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
}

void LoginScript::SetSelected(eSelectedSpace e)
{
	switch (e)
	{
	case LoginScript::eUSER:
		Selected = User;
		break;
	case LoginScript::ePASS:
		Selected = Pass;
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