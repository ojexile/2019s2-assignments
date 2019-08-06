#include "HoleScript.h"
#include "AudioManager.h"
#include "BallScript.h"
HoleScript::HoleScript()
{
}

HoleScript::~HoleScript()
{
}
void HoleScript::Collide(GameObject* go)
{
	if (go->GetComponent<BallScript>())
	{
		AudioManager::GetInstance()->Play3D("fart.wav", {});
		Destroy(go);
	}
}