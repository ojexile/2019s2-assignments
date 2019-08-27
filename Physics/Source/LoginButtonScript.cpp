#include "LoginButtonScript.h"
#include "InputManager.h"
#include "UIButtonComponent.h"
#include "LoginScript.h"

LoginButtonScript::LoginButtonScript(GameObject* LoginGO, GameObject * User, GameObject * Pass, GameObject * LoginLocal, GameObject * CreateLocal)
	: m_LoginGO(LoginGO)
	, m_User(User)
	, m_Pass(Pass)
	, m_LoginLocal(LoginLocal)
	, m_CreateLocal(CreateLocal)
{
}

LoginButtonScript::~LoginButtonScript()
{
}

void LoginButtonScript::Update(double dt)
{
	bool bClick = InputManager::GetInstance()->GetInputStrength("Click");

	if (bClick)
	{
		if (m_LoginLocal->GC(UIButtonComponent)->GetHover())
		{
			m_LoginGO->GetComponent<LoginScript>()->LoginLocal();
		}
		else if (m_CreateLocal->GC(UIButtonComponent)->GetHover())
		{
			m_LoginGO->GetComponent<LoginScript>()->CreateLocal();
		}
		else if (m_User->GC(UIButtonComponent)->GetHover())
		{
			m_User->RENDER->SetAlpha(1.f);
			m_User->RENDER->SetColor(.2f);

			m_Pass->RENDER->SetAlpha(.5f);
			m_Pass->RENDER->SetColor(.1f);

			m_LoginGO->GC(LoginScript)->SetSelected(LoginScript::eUSER);
		}
		else if (m_Pass->GC(UIButtonComponent)->GetHover())
		{
			m_Pass->RENDER->SetAlpha(1.f);
			m_Pass->RENDER->SetColor(.2f);

			m_User->RENDER->SetAlpha(.5f);
			m_User->RENDER->SetColor(.1f);

			m_LoginGO->GC(LoginScript)->SetSelected(LoginScript::ePASS);
		}
	}
}