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
	const float fBufferTime = 0.5f;
	if (Time::GetInstance()->GetElapsedTimeF() - m_fLastPopSoundTime > fBufferTime)
	{
		m_fLastPopSoundTime = Time::GetInstance()->GetElapsedTimeF();
		AudioManager::GetInstance()->Play3D("pop.wav", {});
	}
}