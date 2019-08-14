#include "WeaponScript.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"
//Temporary
#include "DataContainer.h"

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
	//if (m_Projectile)
	//{
	//	delete m_Projectile;
	//	m_Projectile = nullptr;
	//}
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
		case PartScript::STOCK:
		{
			m_iMagazineRounds_Max = m_iMagazineRounds_Max + go->PART->GetMultiplier();
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
		case PartScript::STOCK:
		{
			m_iMagazineRounds_Max = m_iMagazineRounds_Max - go->PART->GetMultiplier();
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
	SpawnPos.y += 0.5f;

	GameObject* bullet = Instantiate(m_Projectile, SpawnPos);
	bullet->RIGID->SetAffectedByGravity(false);
	bullet->RIGID->AddForce(m_fBulletForce * dir);

	DamageEquippedParts(m_ScopeParts, deltaTime);
	DamageEquippedParts(m_MuzzleParts, deltaTime);
	DamageEquippedParts(m_GripParts, deltaTime);
	DamageEquippedParts(m_StockParts, deltaTime);
	--m_iMagazineRounds;

}

void WeaponScript::ReloadWeapon(void)
{
	if (m_iMagazineRounds == m_iMagazineRounds_Max)
		return;

	int refillAmt = m_iMagazineRounds_Max - m_iMagazineRounds;

	m_iAmmo = m_iAmmo - refillAmt;
	m_iMagazineRounds = m_iMagazineRounds + refillAmt;
}

void WeaponScript::AddPart(GameObject* part)
{
	if (!part->PART)
		return;

	if (part->PART->GetPartType() == PartScript::WEAPON)
	{
		switch (part->PART->GetSlotType())
		{
		case PartScript::SCOPE:
		{
			m_ScopeParts.push_back(part);
			break;
		}
		case PartScript::MUZZLE:
		{
			m_MuzzleParts.push_back(part);
			part->TRANS->SetRelativePosition(2 * m_MuzzleParts.size(),0,0);

			break;
		}
		case PartScript::STOCK:
		{
			m_StockParts.push_back(part);
			break;
		}
		case PartScript::GRIP:
		{
			m_GripParts.push_back(part);
			break;
		}
		default:
			break;
		}
		//Update parts after attaching a part
		UpdateStats(part, true);
	}
}

void WeaponScript::DestroyPart(std::vector<GameObject*>& m_vector, GameObject* target)
{
	std::vector<GameObject*>::iterator it = m_vector.end() - 1;
	while (m_vector.size() > 0)
	{
		GameObject* go = static_cast<GameObject*>(*it);

		if (target == go)
		{

			UpdateStats(go, false);

			////Temporary fix, Destroy function does not destroy child of gun
			//go->RENDER->SetActive(false);
			
		 Destroy(go);
			m_vector.pop_back();
			break;
		}
		else
		{
			--it;
			UpdateStats(go, false);
			
			////Temporary fix, Destroy function does not destroy child of gun
			//go->RENDER->SetActive(false);
			//
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
			GameObject* go = static_cast<GameObject*>(*it);
			if (go->PART->DecreaseDurability(deltaTime))
				DestroyPart(m_vector, go);
			if (m_vector.size() == 0)
				break;
		}
	}
}