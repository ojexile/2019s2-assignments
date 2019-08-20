#include "WeaponScript.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"
#include "MiscellaneousPartScript.h"


WeaponScript::WeaponScript(GameObject* Projectile, int iBulletsFiredCount, int iMagazineRounds, int iMagazineRounds_Max, int iAmmo, int iAmmo_Max, float fFirerate, float fBulletSpread, float fBulletForce, FIRING_MODE FiringMode)
	: m_iBulletsFiredCount(iBulletsFiredCount),
	m_iMagazineRounds(iMagazineRounds),
	m_iMagazineRounds_Max(iMagazineRounds_Max),
	m_iAmmo(iAmmo),
	m_iAmmo_Max(iAmmo_Max),
	m_fFirerate(fFirerate),
	m_fBulletSpread(fBulletSpread),
	m_fBulletForce(fBulletForce),
	m_Projectile(Projectile),
	m_FiringMode(FiringMode),
	m_fBufferTime(fFirerate),
	m_bSingleFired(false)
{
}

WeaponScript::~WeaponScript()
{

}

void WeaponScript::PullTrigger(const Vector3& dir, const double deltaTime)
{
	if (!m_Projectile)
		return;

	if (m_iMagazineRounds > 0 && m_fBufferTime > m_fFirerate)
	{
		m_fBufferTime = 0.f;

		switch (m_FiringMode)
		{
		case SINGLE:
		{
			if (!m_bSingleFired)
			{
				FireWeapon(dir, deltaTime);
				m_bSingleFired = true;
			}
			break;
		}
		case AUTO:
		{
			FireWeapon(dir, deltaTime);
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void WeaponScript::ReleaseTrigger()
{
	m_bSingleFired = false;
}

void WeaponScript::Update(double deltaTime)
{
	m_fBufferTime += (float)deltaTime;

	if (InputManager::GetInstance()->GetInputStrength("Reload"))
		ReloadWeapon();
}

void WeaponScript::UpdateStats(GameObject* go, bool Multiply)
{
	if (Multiply)
	{
		switch (go->PART->GetSlotType())
		{
		case PartScript::SCOPE:
		{
			m_fBulletSpread = m_fBulletSpread * go->PART->GetMultiplier();
			break;
		}
		case PartScript::MUZZLE:
		{
			m_fFirerate = m_fFirerate * go->PART->GetMultiplier();
			break;
		}
		case PartScript::CLIP:
		{
			m_iMagazineRounds_Max = m_iMagazineRounds_Max + static_cast<int>(go->PART->GetMultiplier());
			break;
		}
		case PartScript::GRIP:
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
		case PartScript::SCOPE:
		{
			m_fBulletSpread = m_fBulletSpread / go->PART->GetMultiplier();
			break;
		}
		case PartScript::MUZZLE:
		{
			m_fFirerate = m_fFirerate / go->PART->GetMultiplier();
			break;
		}
		case PartScript::CLIP:
		{
			m_iMagazineRounds_Max = m_iMagazineRounds_Max - static_cast<int>(go->PART->GetMultiplier());
			Math::Clamp(m_iMagazineRounds, m_iMagazineRounds, m_iMagazineRounds_Max);
			break;
		}
		case PartScript::GRIP:
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

void WeaponScript::FireWeapon(const Vector3& dir, const double deltaTime)
{
	Vector3 SpawnPos = GetPosition();
	Vector3 direction = dir;

	direction.x = direction.x + Math::RandFloatMinMax(-m_fBulletSpread, m_fBulletSpread);
	direction.y = direction.y + Math::RandFloatMinMax(0, m_fBulletSpread) / 5;
	direction.z = direction.z + Math::RandFloatMinMax(-m_fBulletSpread, m_fBulletSpread);
	
	direction.Normalize();

	GameObject* bullet = Instantiate(m_Projectile, SpawnPos);
	bullet->RIGID->SetAffectedByGravity(false);
	bullet->RIGID->AddForce(m_fBulletForce * direction);

	DamageEquippedParts(m_ScopeParts, deltaTime);
	DamageEquippedParts(m_MuzzleParts, deltaTime);
	DamageEquippedParts(m_GripParts, deltaTime);
	DamageEquippedParts(m_StockParts, deltaTime);
	--m_iMagazineRounds;
}

void WeaponScript::ReloadWeapon(void)
{
	if (m_iMagazineRounds == m_iMagazineRounds_Max || m_iMagazineRounds > m_iMagazineRounds_Max)
		return;

	int refillAmt = m_iMagazineRounds_Max - m_iMagazineRounds;

	m_iAmmo = m_iAmmo - refillAmt;
	m_iMagazineRounds = m_iMagazineRounds + refillAmt;
}

void WeaponScript::EquipPart(GameObject* part, PartScript::SLOT_TYPE slot)
{
	if (!part->PART)
		return;
	
	part->RIGID->SetAffectedByGravity(false);
	
	if(part->PART->GetPartType() == PartScript::ALL)
		part->PART->SetSlotType(slot);

	if (part->PART->GetPartType() == PartScript::WEAPON)
	{
		switch (part->PART->GetSlotType())
		{
		case PartScript::SCOPE:
		{
			m_ScopeParts.push_back(part);
			part->TRANS->SetRelativePosition(-0.7f + (0.25f * m_ScopeParts.size()), 0.2f, 0.f);
			break;
		}
		case PartScript::MUZZLE:
		{
			m_MuzzleParts.push_back(part);
			part->TRANS->SetRelativePosition(-0.2f + (0.7f * m_MuzzleParts.size()), 0, 0);

			break;
		}
		case PartScript::CLIP:
		{
			m_StockParts.push_back(part);
			part->TRANS->SetRelativePosition(-0.45f + (0.05f * m_StockParts.size()), -0.5f* m_StockParts.size(), 0);
			break;
		}
		case PartScript::GRIP:
		{
			m_GripParts.push_back(part);
			part->TRANS->SetRelativePosition((-1.0f * m_GripParts.size()), 0, 0);
			break;
		}
		default:
			break;
		}
		//Update parts after attaching a part
		UpdateStats(part, true);
	}
	else if(part->PART->GetPartType() == PartScript::MISC)
	{
		switch (part->PART->GetSlotType())
		{
		case PartScript::SCOPE:
		{
			m_ScopeParts.push_back(part);
			part->TRANS->SetRelativePosition(-0.7f + (0.25f * m_ScopeParts.size()), 0.2f, 0.f);
			break;
		}
		case PartScript::MUZZLE:
		{
			m_MuzzleParts.push_back(part);
			part->TRANS->SetRelativePosition(-0.2f + (0.7f * m_MuzzleParts.size()), 0, 0);

			break;
		}
		case PartScript::CLIP:
		{
			m_StockParts.push_back(part);
			part->TRANS->SetRelativePosition(-0.45f + (0.05f * m_StockParts.size()), -0.5f* m_StockParts.size(), 0);
			break;
		}
		case PartScript::GRIP:
		{
			m_GripParts.push_back(part);
			part->TRANS->SetRelativePosition((-1.0f * m_GripParts.size()), 0, 0);
			break;
		}
		default:
			break;
		}
		part->MISCPART->Effect();
	}
}


void WeaponScript::DestroyPart(std::vector<GameObject*>& m_vector, GameObject* target)
{
	std::vector<GameObject*>::iterator it = m_vector.end() - 1;
	while (m_vector.size() > 0)
	{
		GameObject* go = static_cast<GameObject*>(*it);
		PartScript::PART_TYPE type = go->PART->GetPartType();
		
		if (target == go)
		{

			if (type == PartScript::PART_TYPE::WEAPON)
				UpdateStats(go, false);
			else
				go->MISCPART->RevertEffect();

			Destroy(go);
			m_vector.pop_back();
			break;
		}
		else
		{
			--it;
			
			if (type == PartScript::PART_TYPE::WEAPON)
				UpdateStats(go, false);
			else
				go->MISCPART->RevertEffect();

			Destroy(go);
			m_vector.pop_back();
		}
	}
}

void WeaponScript::DamageEquippedParts(std::vector<GameObject*>& m_vector, const double deltaTime)
{
	if (m_vector.size() > 0)
	{
		for (auto it = m_vector.begin(); it != m_vector.end(); ++it)
		{
			if (m_vector.size() == 0)
				break;

			GameObject* go = static_cast<GameObject*>(*it);
			if (go->PART->DecreaseDurability(deltaTime))
				DestroyPart(m_vector, go);
			
		}
	}
}


void WeaponScript::SetAmmo(int Ammo)
{
	m_iAmmo = Ammo;
}

void WeaponScript::SetMaxAmmo(int Ammo_Max)
{
	m_iAmmo_Max = Ammo_Max;
}

void WeaponScript::SetBulletsFired(int BulletsFired)
{
	m_iBulletsFiredCount = BulletsFired;
}

void WeaponScript::SetMagazineRounds(int MagRounds)
{
	m_iMagazineRounds = MagRounds;
}

void WeaponScript::SetMaxMagazineRounds(int MagRounds_Max)
{
	m_iMagazineRounds_Max = MagRounds_Max;
}

void WeaponScript::SetFireRate(float FireRate)
{
	m_fFirerate = FireRate;
}

void WeaponScript::SetBulletSpread(float BulletSpread)
{
	m_fBulletSpread = BulletSpread;
}

int WeaponScript::GetAmmo()
{
	return m_iAmmo;
}

int WeaponScript::GetMaxAmmo()
{
	return m_iAmmo_Max;
}

int WeaponScript::GetBulletsFired()
{
	return m_iBulletsFiredCount;
}

int WeaponScript::GetMagazineRounds()
{
	return m_iMagazineRounds;
}

int WeaponScript::GetMaxMagazineRounds()
{
	return m_iMagazineRounds_Max;
}

float WeaponScript::GetFireRate()
{
	return m_fFirerate;
}

float WeaponScript::GetBulletSpread()
{
	return m_fBulletSpread;
}