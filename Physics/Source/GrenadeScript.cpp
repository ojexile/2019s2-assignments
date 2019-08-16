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
	/*DestroySelf();*/
}

void GrenadeScript::PullPin(void)
{
	m_bIsGrenadeCooking = true;
}

void GrenadeScript::ThrowGrenade(const Vector3& dir, const GameObject* GrenadeRef, const double deltaTime)
{
	if (!m_bIsGrenadeCooking)
		return;

	float scalarForce = 20.f;
	Vector3 arcDir = dir.Normalized();
	arcDir.y = arcDir.y + 2;
	Vector3 SpawnPos = GetPosition();

	GameObject* Grenade = Instantiate(GrenadeRef, SpawnPos);
	Grenade->RIGID->AddForce(20 * dir);
}