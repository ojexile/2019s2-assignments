#include "BulletScript.h"
#include "TransformComponent.h"
#include "Time.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
#include "EnemyAIScript.h"
#include "ChengPlayerScript.h"
#define XGRAV 0
BulletScript::BulletScript(const float fLifeTime, float damage)
	: m_fLifeTime(fLifeTime)
	, m_fDamage(damage)
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
	m_fCurrentLife += (float)dt;
	if (m_fCurrentLife >= m_fLifeTime)
	{
		DestroySelf();
		return;
	}
	//ChengRigidbody* rb = GetComponent<ChengRigidbody>();
	//if (GetComponent<TransformComponent>()->GetPosition().x > 0)
	//	rb->SetGravityX(-XGRAV);
	//else
	//	rb->SetGravityX(XGRAV);
	//GetTransform()->SetPosition(GetPosition().x, 10, GetPosition().z);
}
void BulletScript::Collide(GameObject* go)
{
	ChengRigidbody* rb = GetComponent<ChengRigidbody>();
	const float fBufferTime = 0.5f;
	if (Time::GetInstance()->GetElapsedTimeF() - m_fLastPopSoundTime > fBufferTime)
	{
		m_fLastPopSoundTime = Time::GetInstance()->GetElapsedTimeF();
		// z is left
		Vector3 pos = GetPosition();
		AudioManager::GetInstance()->Play3D("thump.wav", pos, rb->GetVel().LengthSquared() * .001f);
	}
	EnemyAIScript* es = go->GetComponent<EnemyAIScript>();
	if (es)
	{
		es->Damage(m_fDamage);
		DestroySelf();
		return;
	}
	ChengPlayerScript* ps = go->GetComponent<ChengPlayerScript>();
	if (ps)
	{
		ps->Damage(m_fDamage);
		DestroySelf();
		return;
	}
}