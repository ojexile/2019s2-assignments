#include "GunScript.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"
#include "ProjectileScript.h"
#include "ExplodeAugment.h"

GunScript::GunScript(GameObject* Projectile, int iBulletsFiredCount, int iMagazineRounds, int iMagazineRounds_Max, float fReloadTime, float fFirerate, float fBulletSpread, float fBulletForce)
	: m_iBulletsFiredCount(iBulletsFiredCount),
	m_iMagazineRounds(iMagazineRounds),
	m_iMagazineRounds_Max(iMagazineRounds_Max),
	m_fReloadTime(fReloadTime),
	m_fReloadElapsedTime(0.f),
	m_fFirerate(fFirerate),
	m_fBulletSpread(fBulletSpread),
	m_fBulletForce(fBulletForce),
	m_Projectile(Projectile),
	m_fBufferTime(fFirerate),
	m_bIsReloading(false),
	m_bSingleFired(false)
{
}

GunScript::~GunScript()
{
}

void GunScript::PullTrigger(const Vector3& dir, const double deltaTime)
{
	if (!m_Projectile || m_bIsReloading)
		return;

	if (m_iMagazineRounds <= 0)
	{
		ReloadWeapon();
	}
	if (m_iMagazineRounds > 0 && m_fBufferTime > m_fFirerate)
	{
		m_fBufferTime = 0.f;
		FireWeapon(dir, deltaTime);
	}
}

void GunScript::ReleaseTrigger()
{
	m_bSingleFired = false;
}

void GunScript::Update(double deltaTime)
{
	m_fBufferTime += (float)deltaTime;

	if (m_bIsReloading)
	{
		GetChild(0)->SetActive(true);
		m_fReloadElapsedTime += (float)deltaTime;
	}
	else
		GetChild(0)->SetActive(false);

	if (m_fReloadElapsedTime >= m_fReloadTime && m_bIsReloading)
		ReloadWeapon();

	m_iMagazineRounds = Math::Clamp(m_iMagazineRounds, 0, m_iMagazineRounds_Max);
}

void GunScript::UpdateStats(GameObject* go, bool Multiply)
{
	if (Multiply)
	{
		switch (go->PART->GetSlotType())
		{
		case WeaponPartScript::SCOPE:
		{
			m_fBulletSpread = m_fBulletSpread * go->PART->GetMultiplier();
			break;
		}
		case WeaponPartScript::MUZZLE:
		{
			m_fFirerate = m_fFirerate * go->PART->GetMultiplier();
			break;
		}
		case WeaponPartScript::CLIP:
		{
			m_iMagazineRounds_Max = m_iMagazineRounds_Max + static_cast<int>(go->PART->GetMultiplier());
			break;
		}
		case WeaponPartScript::GRIP:
		{
			//Need another variable to edit, temporarily bullet spread
			m_fBulletSpread = m_fBulletSpread * go->PART->GetMultiplier();
			break;
		}
		default:
			break;
		}
	}
	else
	{
		switch (go->PART->GetSlotType())
		{
		case WeaponPartScript::SCOPE:
		{
			m_fBulletSpread = m_fBulletSpread / go->PART->GetMultiplier();
			break;
		}
		case WeaponPartScript::MUZZLE:
		{
			m_fFirerate = m_fFirerate / go->PART->GetMultiplier();
			break;
		}
		case WeaponPartScript::CLIP:
		{
			m_iMagazineRounds_Max = m_iMagazineRounds_Max - static_cast<int>(go->PART->GetMultiplier());
			Math::Clamp(m_iMagazineRounds, m_iMagazineRounds, m_iMagazineRounds_Max);
			break;
		}
		case WeaponPartScript::GRIP:
		{
			//Need another variable to edit, temporarily bullet spread
			m_fBulletSpread = m_fBulletSpread / go->PART->GetMultiplier();
			break;
		}
		default:
			break;
		}
	}
}

void GunScript::FireWeapon(const Vector3& dir, const double deltaTime)
{
	Vector3 SpawnPos = GetPosition();
	Vector3 direction = dir;

	Mtx44 recoil;
	recoil.SetToRotation(Math::RandFloatMinMax(-m_fBulletSpread, m_fBulletSpread), 0, 1, 0);

	direction = recoil * direction;

	direction.Normalize();

	GameObject* bullet = Instantiate(m_Projectile, SpawnPos);
	bullet->RIGID->SetAffectedByGravity(false);
	bullet->RIGID->AddForce(m_fBulletForce * direction);

	ApplyAugmentOnBullet(m_ScopeParts, bullet);
	ApplyAugmentOnBullet(m_MuzzleParts, bullet);
	ApplyAugmentOnBullet(m_GripParts, bullet);
	ApplyAugmentOnBullet(m_StockParts, bullet);

	DamageEquippedParts(m_ScopeParts, deltaTime);
	DamageEquippedParts(m_MuzzleParts, deltaTime);
	DamageEquippedParts(m_GripParts, deltaTime);
	DamageEquippedParts(m_StockParts, deltaTime);
	--m_iMagazineRounds;
}

void GunScript::ReloadWeapon(void)
{
	if (m_iMagazineRounds == m_iMagazineRounds_Max || m_iMagazineRounds > m_iMagazineRounds_Max)
		return;

	if (!m_bIsReloading)
	{
		m_bIsReloading = true;
		RYAN_LOG("IS RELOADING");
	}
	else if (m_fReloadElapsedTime >= m_fReloadTime && m_bIsReloading)
	{
		int refillAmt = m_iMagazineRounds_Max - m_iMagazineRounds;
		m_iMagazineRounds = m_iMagazineRounds + refillAmt;

		m_bIsReloading = false;
		m_fReloadElapsedTime = 0.f;
		RYAN_LOG("RELOADED");
	}
}

void GunScript::EquipPart(GameObject* part, WeaponPartScript::SLOT_TYPE slot)
{
	if (!part->PART)
		return;

	part->RIGID->SetAffectedByGravity(false);

	//Apply augment if present
	if (part->PART->GetAugment())
		part->PART->GetAugment()->PassiveEffect();

	switch (part->PART->GetSlotType())
	{
	case WeaponPartScript::SCOPE:
	{
		m_ScopeParts.push_back(part);
		part->TRANS->SetRelativePosition(-1.f + (0.25f * m_ScopeParts.size()), 0.35f, 0.f);

		UpdateStats(part, true);
		return;
	}
	case WeaponPartScript::MUZZLE:
	{
		m_MuzzleParts.push_back(part);
		part->TRANS->SetRelativePosition(-0.2f + (0.7f * m_MuzzleParts.size()), 0, 0);

		UpdateStats(part, true);
		return;
	}
	case WeaponPartScript::CLIP:
	{
		m_StockParts.push_back(part);
		part->TRANS->SetRelativePosition(-0.55f + (0.05f * m_StockParts.size()), -0.5f* m_StockParts.size(), 0);

		UpdateStats(part, true);
		return;
	}
	case WeaponPartScript::GRIP:
	{
		m_GripParts.push_back(part);
		part->TRANS->SetRelativePosition(-1.2f + (-1.0f * m_GripParts.size()), 0, 0);

		UpdateStats(part, true);
		return;
	}
	default:
		break;
	}

	RYAN_LOG("Part Not equipped");
	Destroy(part);
}

void GunScript::DestroyPart(std::vector<GameObject*>& m_vector, GameObject* target)
{
	while (m_vector.size() > 0)
	{
		GameObject* go = static_cast<GameObject*>(*(m_vector.rbegin()));

		if (go->PART->GetAugment())
			go->PART->GetAugment()->RemovePassive();

		if (target == go)
		{
			UpdateStats(go, false);
			Destroy(go);
			m_vector.pop_back();
			break;
		}
		else
		{
			UpdateStats(go, false);
			Destroy(go);
			m_vector.pop_back();
		}
	}
}

void GunScript::DamageEquippedParts(std::vector<GameObject*>& m_vector, const double deltaTime)
{
	if (m_vector.size() > 0)
	{
		for (auto it = m_vector.begin(); it != m_vector.end(); ++it)
		{
			if (m_vector.size() == 0)
				break;

			GameObject* go = static_cast<GameObject*>(*it);
			if (go->PART->DecreaseDurability(deltaTime))
			{
				DestroyPart(m_vector, go);
				break;
			}
		}
	}
}

void GunScript::ApplyAugmentOnBullet(std::vector<GameObject*>& m_vector, GameObject* go)
{
	if (m_vector.size() == 0)
		return;

	for (auto it = m_vector.begin(); it != m_vector.end(); ++it)
	{
		//Give the bullet a copy of the augment
		GameObject* wp = static_cast<GameObject*>(*it);
		if (wp->PART->GetAugment())
			go->GetComponent<ProjectileScript>()->AddAugment(wp->PART->GetAugment()->Clone());
	}
}

void GunScript::SetBulletsFired(int BulletsFired)
{
	m_iBulletsFiredCount = BulletsFired;
}

void GunScript::SetMagazineRounds(int MagRounds)
{
	m_iMagazineRounds = MagRounds;
}

void GunScript::SetMaxMagazineRounds(int MagRounds_Max)
{
	m_iMagazineRounds_Max = MagRounds_Max;
}

void GunScript::SetFireRate(float FireRate)
{
	m_fFirerate = FireRate;
}

void GunScript::SetBulletSpread(float BulletSpread)
{
	m_fBulletSpread = BulletSpread;
}

void GunScript::SetReloadTime(float ReloadTime)
{
	m_fReloadTime = ReloadTime;
}

void GunScript::AffectReloadTime(float Multiplier)
{
	m_fReloadTime = m_fReloadTime * Multiplier;
}

int GunScript::GetBulletsFired()
{
	return m_iBulletsFiredCount;
}

int GunScript::GetMagazineRounds()
{
	return m_iMagazineRounds;
}

int GunScript::GetMaxMagazineRounds()
{
	return m_iMagazineRounds_Max;
}

float GunScript::GetFireRate()
{
	return m_fFirerate;
}

float GunScript::GetBulletSpread()
{
	return m_fBulletSpread;
}

float GunScript::GetReloadElapsedTime()
{
	return m_fReloadElapsedTime;
}

float GunScript::GetReloadTime()
{
	return m_fReloadTime;
}

GameObject* GunScript::GetBullet()
{
	return m_Projectile;
}

bool GunScript::IsReloading()
{
	return m_bIsReloading;
}