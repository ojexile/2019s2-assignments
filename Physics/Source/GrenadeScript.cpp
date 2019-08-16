#include "GrenadeScript.h"
#include "EntityScript.h"


GrenadeScript::GrenadeScript(float Lifespan, float Damage, float ExplosionRadius)
	: ProjectileScript(Lifespan, Damage)
	, m_fExplosionRadius(ExplosionRadius)
	, m_bIsGrenadeCooking(false)
	, m_bHasExploded(false)
{
	m_iGrenadeCount = 5;
	m_fExplosionDamage = m_fDamage * 2;
}


GrenadeScript::~GrenadeScript()
{
}

void GrenadeScript::Update(double deltaTime)
{
	if (m_fLifespan >= 0.f)
		m_fLifespan = m_fLifespan - static_cast<float>(deltaTime);
	else
	{
		if (!m_bHasExploded)
			Explode();
		else
			DestroySelf();
	}
}

void GrenadeScript::Explode(void)
{
	TRANS->SetScale(m_fExplosionRadius);

	m_fLifespan = m_fLifespan + 0.005f;
	m_bHasExploded = true;
}

void GrenadeScript::Collide(GameObject* go)
{
	EntityScript* es = go->GetComponent<EntityScript>(true);	
	
	if (es)
	{
		if (m_bHasExploded)
		{
			Vector3 relDir = go->TRANS->GetPosition() - GetPosition();

			es->Damage(m_fExplosionDamage);
			go->RIGID->AddForce(relDir.Normalize() * 1000);
		}
		else
			es->Damage(m_fDamage);
	}
}

void GrenadeScript::PullPin(void)
{
	if (m_iGrenadeCount > 0 && !m_bIsGrenadeCooking)
	{
		RYAN_LOG("GRENADE THROW");
		m_bIsGrenadeCooking = true;
	}
}

void GrenadeScript::ThrowGrenade(const Vector3& dir, const GameObject* GrenadeRef, const float deltaTime)
{
	if (!m_bIsGrenadeCooking)
		return;

	float scalarForce = 20.f;
	Vector3 arcDir = dir.Normalized();
	arcDir.y = arcDir.y + 4;
	Vector3 SpawnPos = GetPosition();

	GameObject* Grenade = Instantiate(GrenadeRef, SpawnPos);
	Grenade->RIGID->AddForce(1000 * dir);
	Grenade->RIGID->SetAffectedByGravity(true);

	--m_iGrenadeCount;

	m_bIsGrenadeCooking = false;
}