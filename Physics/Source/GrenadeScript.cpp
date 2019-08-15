#include "GrenadeScript.h"
#include "EntityScript.h"


GrenadeScript::GrenadeScript(double Lifespan, double Damage, float ExplosionRadius)
	: ProjectileScript(Lifespan, Damage)
	, m_fExplosionRadius(ExplosionRadius)
{
}


GrenadeScript::~GrenadeScript()
{
}

void GrenadeScript::Update(double deltaTime)
{
	if (m_dLifespan >= 0.f)
		m_dLifespan = m_dLifespan - deltaTime;
	else
		Explode();
}

void GrenadeScript::Explode(void)
{
	TRANS->SetScale(5);

	m_dLifespan = m_dLifespan + 0.5;
}

void GrenadeScript::Collide(GameObject* go)
{
	EntityScript* es = go->GetComponent<EntityScript>(true);	
	
	if (es)
	{
		es->Damage(m_dDamage);
	}
	DestroySelf();
}