#include "ReloadingAugment.h"
#include "ProjectileScript.h"
#include "GunScript.h"


ReloadingAugment::ReloadingAugment()
{
	m_AugmentType = WEAPON;
	m_fMultiplier = 0.75f;
	m_Name = "Reloading Augment";
}


ReloadingAugment::~ReloadingAugment()
{
}

void ReloadingAugment::ActiveEffect(Component* proj, GameObject* go)
{
	proj->GetComponent<ProjectileScript>()->SetLifespan(0.01f);
}

void ReloadingAugment::PassiveEffect()
{
	if (!m_GunRef)
		return;

	m_GunRef->GUN->AffectReloadTime(m_fMultiplier);
}

void ReloadingAugment::RemovePassive()
{
	if (!m_GunRef)
		return;

	m_GunRef->GUN->AffectReloadTime(1 / m_fMultiplier);
}