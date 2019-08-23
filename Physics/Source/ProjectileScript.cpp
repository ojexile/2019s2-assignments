#include "ProjectileScript.h"
#include "EntityScript.h"

ProjectileScript::ProjectileScript(float lifespan, float Damage)
	: m_fLifespan(lifespan),
	m_fDamage(Damage)
{
}

ProjectileScript::~ProjectileScript()
{
	while (m_AugmentList.size() > 0)
	{
		Component* comp = static_cast<Component*>(*(m_AugmentList.rbegin()));
		delete comp;
		m_AugmentList.pop_back();

	}
}

void ProjectileScript::Update(double deltaTime)
{
	if (m_fLifespan > 0.f)
		m_fLifespan = m_fLifespan - static_cast<float>(deltaTime);
	else
		DestroySelf();
}

float ProjectileScript::GetDamage()
{
	return m_fDamage;
}

float ProjectileScript::GetLifespan()
{
	return m_fLifespan;
}

void ProjectileScript::SetDamage(float damage)
{
	this->m_fDamage = damage;
}

void ProjectileScript::SetLifespan(float lifespan)
{
	this->m_fLifespan = lifespan;
}

void ProjectileScript::Collide(GameObject* go)
{
	EntityScript* es = go->GetComponent<EntityScript>(true);
	if (es)
	{
		es->Damage(m_fDamage);
		ActivateEffects(this, go);
		RIGID->SetVel(Vector3(0, 0, 0));
		m_fLifespan = 0.01f;
	}
}

void ProjectileScript::AddAugment(Component* augment)
{
	m_AugmentList.push_back(augment);
}

bool ProjectileScript::ActivateEffects(ProjectileScript* proj, GameObject* go)
{
	bool HasAugment = false;

	for (auto it = m_AugmentList.begin(); it != m_AugmentList.end(); ++it)
	{
		Augment* augment = static_cast<Augment*>(*it);
		augment->ActiveEffect(proj, go);
	}

	return HasAugment;
}