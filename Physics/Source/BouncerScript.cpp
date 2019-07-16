#include "BouncerScript.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
#include "RenderComponent.h"
BouncerScript::BouncerScript(float bounceForce)
{
	m_fBounceForce = bounceForce;
}

BouncerScript::~BouncerScript()
{
}

void BouncerScript::Update(double dt)
{
}
void BouncerScript::Collide(GameObject* go)
{
	AudioManager::GetInstance()->PlayBGM("pop.wav");
	ChengRigidbody* rigid = go->GetComponent<ChengRigidbody>();
	rigid->IncrementForce(rigid->GetVel() * m_fBounceForce);
	GetComponent<RenderComponent>()->SetColor({ 0,1,1 });
	CHENG_LOG("Bounce");
}