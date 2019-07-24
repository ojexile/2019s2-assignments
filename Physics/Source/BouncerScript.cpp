#include "BouncerScript.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
#include "RenderComponent.h"
#include "AnimatedMesh.h"
#include "WorldValues.h"

#define MAX_HEALTH 100.f
BouncerScript::BouncerScript(float bounceForce, ScoreScript* scoreScript, bool isPlayer)
	: m_ScoreScript(scoreScript)
	, m_bIsPlayer(isPlayer)
{
	m_fBounceForce = bounceForce;
	m_bTriggered = false;
	m_fTriggerTime = 0;
	m_fHealth = MAX_HEALTH;
}

BouncerScript::~BouncerScript()
{
}

void BouncerScript::Update(double dt)
{
	if (m_bTriggered)
	{
		if (Time::GetInstance()->GetElapsedTimeF() > m_fTriggerTime + TRIGGER_DURATION)
		{
			m_bTriggered = false;
			GetComponent<RenderComponent>()->SetColor({ m_fHealth / MAX_HEALTH,m_fHealth / 2 / MAX_HEALTH, m_fHealth / 2 / MAX_HEALTH });
		}
	}
	if (m_fHealth <= 0)
	{
		// TODO Play death audio
		if (!m_bIsPlayer)
		{
			m_ScoreScript->IncrementScore(20);
			DestroySelf();
		}
	}
}
void BouncerScript::Collide(GameObject* go)
{
	AudioManager::GetInstance()->Play3D("boing.wav", {});
	float fDamage = 0.5f * go->GetComponent<ChengRigidbody>()->GetMass() * go->GetComponent<ChengRigidbody>()->GetVel().LengthSquared();
	if (WorldValues::TimeScale > 0)
		fDamage *= 0.001f;
	else
		fDamage *= -0.001f;

	m_fHealth -= fDamage;
	ChengRigidbody * rigid = go->GetComponent<ChengRigidbody>();
	rigid->IncrementForce(rigid->GetVel() * m_fBounceForce);
	GetComponent<RenderComponent>()->SetColor({ 0,1,1 });
	m_bTriggered = true;
	m_fTriggerTime = Time::GetInstance()->GetElapsedTimeF();

	m_ScoreScript->IncrementScore(5);
	//CHENG_LOG("Bounce");
}