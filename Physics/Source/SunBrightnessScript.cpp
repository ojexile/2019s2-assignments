#include "SunBrightnessScript.h"
#include "Light.h"
#include "SceneManager.h"
SunBrightnessScript::SunBrightnessScript()
{
}

SunBrightnessScript::~SunBrightnessScript()
{
}
void SunBrightnessScript::Update(double dt)
{
	Light* Light = SceneManager::GetInstance()->GetScene()->GetLightManager()->GetSceneLights().at(0);
	Light->power -= 0.0001f * (float)dt;
	Light->power = Math::Clamp(Light->power, 0.1f, 2.f);
	Light->position.x -= 1.f * (float)dt;
	GetComponent<TransformComponent>()->SetPosition({ Light->position.x ,Light->position.y + 6,Light->position.z });
}