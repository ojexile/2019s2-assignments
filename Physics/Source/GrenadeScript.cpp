#include "GrenadeScript.h"
#include "EntityScript.h"
#include "AdvancedParticleSpawnerScript.h"

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
	auto spawner = GetComponent<AdvancedParticleSpawnerScript>();
	if (spawner)
	{
		spawner->Trigger();
	}

	RIGID->SetVel(Vector3(0, 0, 0));
	m_fLifespan = 0.5f;
	m_bHasExploded = true;
}

void GrenadeScript::Collide(GameObject* go)
{
	EntityScript* es = go->GetComponent<EntityScript>(true);

	if (es)
	{
		es->Damage((int)m_fDamage);
		Vector3 relDir = go->TRANS->GetPosition() - GetPosition();
		Explode();
		es->Damage((int)m_fExplosionDamage);
		go->RIGID->AddForce(relDir.Normalize() * 50);
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

	Vector3 arcDir = dir;
	arcDir.y = arcDir.y + 10;
	arcDir.Normalized();
	arcDir = arcDir * Math::Max(pow(dir.Length(), 1.2f), 100.f);
	Vector3 SpawnPos = GetPosition();

	GameObject* Grenade = Instantiate(GrenadeRef, SpawnPos);
	Grenade->RIGID->AddForce(arcDir);
	Grenade->RIGID->SetAffectedByGravity(true);

	//--m_iGrenadeCount;

	m_bIsGrenadeCooking = false;
}