#include "WeaponScript.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "TransformComponent.h"

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
	if (m_Projectile)
	{
		delete m_Projectile;
		m_Projectile = nullptr;
	}
}

void WeaponScript::PullTrigger(const Vector3& dir, const double deltaTime)
{

}

void WeaponScript::ReleaseTrigger()
{

}

void WeaponScript::Update(double deltaTime)
{
	m_fBufferTime += (float)deltaTime;

	//Note: use the direct function for now
	if (InputManager::GetInstance()->GetInputStrength("Fire"))
		FireWeapon(Vector3(1,0,0), deltaTime);
	if (!InputManager::GetInstance()->GetInputStrength("Fire") && m_bSingleFired)
		m_bSingleFired = false;

	if (InputManager::GetInstance()->GetInputStrength("Reload"))
		ReloadWeapon();
}

void WeaponScript::UpdateStats(std::queue<GameObject*>& m_UpdatedQueue)
{
	GameObject* go_Front = m_UpdatedQueue.front();
	GameObject* go_Back = m_UpdatedQueue.back();

	switch (go_Front->PART->GetSlotType())
	{
	case PartScript::SCOPE:
	{
		m_fBulletSpread = m_fBulletSpread * go_Back->PART->GetMultiplier();
		break;
	}
	case PartScript::MUZZLE:
	{
		m_fFirerate = m_fFirerate * go_Back->PART->GetMultiplier();
		break;
	}
	case PartScript::STOCK:
	{
		m_iMagazineRounds_Max = m_iMagazineRounds_Max + go_Back->PART->GetMultiplier();
		break;
	}
	case PartScript::GRIP:
	{
		//Need another variable to edit, temporarily bullet spread
		m_fBulletSpread = m_fBulletSpread * go_Back->PART->GetMultiplier();
		break;
	}
	default:
		break;
	}
}

void WeaponScript::FireWeapon(const Vector3& dir, const double deltaTime)
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
				GameObject* bullet = Instantiate(m_Projectile, Vector3(0, 10, 0));
				bullet->RIGID->SetAffectedByGravity(false);
				bullet->RIGID->AddForce(m_fBulletForce * dir);

				--m_iMagazineRounds;
				
				DamageEquippedParts(deltaTime);

				m_bSingleFired = true;
			}
			break;
		}
		case AUTO:
		{
			GameObject* bullet = Instantiate(m_Projectile, Vector3 (0,10,0));
			bullet->RIGID->SetAffectedByGravity(false);
			bullet->RIGID->AddForce(m_fBulletForce * dir);
			
			--m_iMagazineRounds;
			
			DamageEquippedParts(deltaTime);
			break;
		}
		default:
		{
			break;
		} 
		}
	}
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
			m_ScopeParts.push(part);
			UpdateStats(m_ScopeParts);
			break;
		}
		case PartScript::MUZZLE:
		{
			m_MuzzleParts.push(part);
			UpdateStats(m_MuzzleParts);
			break;
		}
		case PartScript::STOCK:
		{
			m_StockParts.push(part);
			UpdateStats(m_StockParts);
			break;
		}
		case PartScript::GRIP:
		{
			m_GripParts.push(part);
			UpdateStats(m_GripParts);
			break;
		}
		default:
			break;
		}
		//Update parts after attaching a part
	}
}

void WeaponScript::RemovePart(std::queue<GameObject*>& m_Queue)
{
	m_Queue.pop();
}

void WeaponScript::DamageEquippedParts(const double deltaTime)
{
	/*for (auto it = m_ScopeParts.front(); it != m_ScopeParts.back(); ++it)
	{
		GameObject* go = static_cast<GameObject*>(it);
		go->PART->DecreaseDurability(deltaTime);
	}

	for (auto it = m_MuzzleParts.front(); it != m_MuzzleParts.back(); ++it)
	{
		GameObject* go = static_cast<GameObject*>(it);
		go->PART->DecreaseDurability(deltaTime);
	}

	for (auto it = m_GripParts.front(); it != m_GripParts.back(); ++it)
	{
		GameObject* go = static_cast<GameObject*>(it);
		go->PART->DecreaseDurability(deltaTime);
	}

	for (auto it = m_StockParts.front(); it != m_StockParts.back(); ++it)
	{
		GameObject* go = static_cast<GameObject*>(it);
		go->PART->DecreaseDurability(deltaTime);
	}*/
}