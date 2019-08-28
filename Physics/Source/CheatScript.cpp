#include "CheatScript.h"
#include "InputManager.h"
#include "RenderingManager.h"
#include "Engine.h"
#include "SceneManager.h"
#include "EntityScript.h"
#include "WorldValues.h"
#include "Application.h"

CheatScript::CheatScript(GameObject * Sheet)
	:m_Sheet(Sheet)
{
}

CheatScript::~CheatScript()
{
}

void CheatScript::Update(double dt)
{
	m_Sheet->SetActive(true);
	if (InputManager::GetInstance()->GetInputStrength("Cheat") > 0)
	{
		if (InputManager::GetInstance()->GetInputStrength("Fog"))
		{
			WorldValues::FogDensity = 1.f;
			Application::GetInstance().GetEngine()->GetRenderManager()->oof = 1.f;
			CHENG_LOG("Cheat Act: ", "FOG");
		}
		else if (InputManager::GetInstance()->GetInputStrength("God"))
		{
			SceneManager::GetInstance()->GetScene()->GetPlayer()->GC(EntityScript)->SetCanDie(false);
			CHENG_LOG("Cheat Act: ", "Gog");
		}
		else if (InputManager::GetInstance()->GetInputStrength("Death"))
		{
			SceneManager::GetInstance()->GetScene()->GetPlayer()->GC(EntityScript)->SetCanDie(true);
			SceneManager::GetInstance()->GetScene()->GetPlayer()->GC(EntityScript)->Damage(10000000);
			CHENG_LOG("Cheat Act: ", "Death");
		}
	}
	else if (InputManager::GetInstance()->GetInputStrength("Cheat") < 0)
	{
		if (InputManager::GetInstance()->GetInputStrength("Fog"))
		{
			WorldValues::FogDensity = 0.1f;
			CHENG_LOG("Cheat Dis: ", "FOG");
		}
		else if (InputManager::GetInstance()->GetInputStrength("God"))
		{
			SceneManager::GetInstance()->GetScene()->GetPlayer()->GC(EntityScript)->SetCanDie(true);
			CHENG_LOG("Cheat Dis: ", "God");
		}
		else if (InputManager::GetInstance()->GetInputStrength("Death"))
		{
			CHENG_LOG("Cheat Dis: ", "Death");
		}
	}
	else
		m_Sheet->SetActive(false);
}