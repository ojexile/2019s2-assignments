#include "BulletScript.h"
#include "TransformComponent.h"
#include "Time.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
#define XGRAV 20
BulletScript::BulletScript(const float fLifeTime)
	:m_fLifeTime(fLifeTime)
{
	m_fCurrentLife = 0;
	m_fLastPopSoundTime = 0;
}

BulletScript::~BulletScript()
{
}

void BulletScript::Update(double dt)
{
	//GetComponent<TransformComponent>()->Translate(100 * (float)dt * m_vDir);
	//--------------------------------------------------------------------------------
	//m_fCurrentLife += (float)dt;
	//if (m_fCurrentLife >= m_fLifeTime)
	//	DestroySelf();
	ChengRigidbody* rb = GetComponent<ChengRigidbody>();
	if (GetComponent<TransformComponent>()->GetPosition().x > 0)
		rb->SetGravityX(-XGRAV);
	else
		rb->SetGravityX(XGRAV);
}
void BulletScript::Collide(GameObject* go)
{
	const float fBufferTime = 0.5f;
	if (Time::GetInstance()->GetElapsedTimeF() - m_fLastPopSoundTime > fBufferTime)
	{
		m_fLastPopSoundTime = Time::GetInstance()->GetElapsedTimeF();
		AudioManager::GetInstance()->Play3D("pop.wav", {});
	}
}