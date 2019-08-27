#include "LoginScript.h"
#include "Application.h"
#include "InputManager.h"

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
		CHENG_LOG("bck");
	}
}