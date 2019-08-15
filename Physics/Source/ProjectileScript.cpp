#include "ProjectileScript.h"

#include "EntityScript.h"

ProjectileScript::ProjectileScript(double lifespan, double Damage)
	: m_dLifespan(lifespan),
	m_dDamage(m_dDamage)
{
}

ProjectileScript::~ProjectileScript()
{
}

void ProjectileScript::Update(double deltaTime)
{
	if (m_dLifespan >= 0.f)
		m_dLifespan = m_dLifespan - deltaTime;
	else
		DestroySelf();
}

double ProjectileScript::getDamage()
{
	return m_dDamage;
}

double ProjectileScript::getLifespan()
{
	return m_dLifespan;
}
void ProjectileScript::Collide(GameObject* go)
{
	EntityScript* es = go->GetComponent<EntityScript>(true);
	if (es)
	{
		es->Damage(m_dDamage);
	}
	DestroySelf();
}