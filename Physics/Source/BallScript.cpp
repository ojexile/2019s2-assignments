#include "BallScript.h"
#include "AudioManager.h"

BallScript::BallScript()
{
}

BallScript::~BallScript()
{
}

void BallScript::Collide(GameObject* go)
{
	AudioManager::GetInstance()->Play3D("pop.wav", {});
}