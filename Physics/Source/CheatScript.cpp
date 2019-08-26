#include "CheatScript.h"
#include "InputManager.h"
#include "RenderingManager.h"
#include "Engine.h"
#include "SceneManager.h"
#include "EntityScript.h"
#include "WorldValues.h"

CheatScript::CheatScript()
{
}

CheatScript::~CheatScript()
{
}

void CheatScript::Update(double dt)
{
	if (InputManager::GetInstance()->GetInputStrength("Cheat") > 0)
	{
		if (InputManager::GetInstance()->GetInputStrength("Fog"))
		{
			WorldValues::FogDensity = 1.f;
			CHENG_LOG("Cheat Act", "FOG");
		}
		else if (InputManager::GetInstance()->GetInputStrength("God"))
		{
			SceneManager::GetInstance()->GetScene()->GetPlayer()->GC(EntityScript)->SetCanDie(false);
			CHENG_LOG("Cheat Act", "God");
		}
	}
	if (InputManager::GetInstance()->GetInputStrength("Cheat") < 0)
	{
		if (InputManager::GetInstance()->GetInputStrength("Fog"))
		{
			WorldValues::FogDensity = 0.1f;
			CHENG_LOG("Cheat Dis", "FOG");
		}
		else if (InputManager::GetInstance()->GetInputStrength("God"))
		{
			SceneManager::GetInstance()->GetScene()->GetPlayer()->GC(EntityScript)->SetCanDie(true);
			CHENG_LOG("Cheat Dis", "God");
		}
	}
}