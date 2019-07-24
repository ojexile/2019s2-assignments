#include "HoleScript.h"
#include "AudioManager.h"
HoleScript::HoleScript()
{
}

HoleScript::~HoleScript()
{
}
void HoleScript::Collide(GameObject* go)
{
	AudioManager::GetInstance()->Play3D("fart.wav", {});
	Destroy(go);
}