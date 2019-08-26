#include "ReloadingAugment.h"
#include "GunScript.h"


ReloadingAugment::ReloadingAugment()
{
	m_AugmentType = WEAPON;
	m_fMultiplier = 0.75f;
}


ReloadingAugment::~ReloadingAugment()
{
}

void ReloadingAugment::ActiveEffect(Component* proj, GameObject* go)
{
	
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