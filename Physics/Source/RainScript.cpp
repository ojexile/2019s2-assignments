#include "RainScript.h"

RainScript::RainScript(GameObject* BounceParticle)
	: m_BounceParticle(BounceParticle)
{
}

RainScript::~RainScript()
{
}
void RainScript::Update(double dt)
{
	if (GetComponent<TransformComponent>()->GetPosition().y <= 0)
	{
		Instantiate(m_BounceParticle, GetComponent<TransformComponent>()->GetPosition());
		DestroySelf();
	}
}