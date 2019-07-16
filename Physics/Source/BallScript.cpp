#include "BallScript.h"
#include "AudioManager.h"
#include "Time.h"

BallScript::BallScript()
{
	m_fLastPopSoundTime = 0;
}

BallScript::~BallScript()
{
}

void BallScript::Collide(GameObject* go)
{
}