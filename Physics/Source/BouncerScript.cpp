#include "BouncerScript.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
#include "RenderComponent.h"

BouncerScript::BouncerScript(float bounceForce)
{
	m_fBounceForce = bounceForce;
	m_bTriggered = false;
	m_fTriggerTime = 0;
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
			GetComponent<RenderComponent>()->SetColor({ 1,1,1 });
		}
	}
}
void BouncerScript::Collide(GameObject* go)
{
	AudioManager::GetInstance()->Play3D("pop.wav", {});
	ChengRigidbody* rigid = go->GetComponent<ChengRigidbody>();
	rigid->IncrementForce(rigid->GetVel() * m_fBounceForce);
	GetComponent<RenderComponent>()->SetColor({ 0,1,1 });
	m_bTriggered = true;
	m_fTriggerTime = Time::GetInstance()->GetElapsedTimeF();
	CHENG_LOG("Bounce");
}