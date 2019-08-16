#include "ProjectileScript.h"

#include "EntityScript.h"

ProjectileScript::ProjectileScript(float lifespan, float Damage)
	: m_fLifespan(lifespan),
	m_fDamage(Damage)
{
}

ProjectileScript::~ProjectileScript()
{
}

void ProjectileScript::Update(double deltaTime)
{
	if (m_fLifespan >= 0.f)
		m_fLifespan = m_fLifespan - static_cast<float>(deltaTime);
	else
		DestroySelf();
}

float ProjectileScript::getDamage()
{
	return m_fDamage;
}

float ProjectileScript::getLifespan()
{
	return m_fLifespan;
}
void ProjectileScript::Collide(GameObject* go)
{
	EntityScript* es = go->GetComponent<EntityScript>(true);
	if (es)
	{
		es->Damage(m_fDamage);
	}
	DestroySelf();
}