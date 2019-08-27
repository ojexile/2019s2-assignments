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
	}
}