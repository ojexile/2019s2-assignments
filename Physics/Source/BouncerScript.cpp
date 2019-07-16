#include "BouncerScript.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
BouncerScript::BouncerScript(float bounceForce)
{
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

	CHENG_LOG("Bounce");
}