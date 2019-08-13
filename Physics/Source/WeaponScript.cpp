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
	if (InputManager::GetInstance()->GetInputStrength("Fire"))
	{
		//Note: use the direct function for now
		FireWeapon(Vector3(1,0,0), deltaTime);
	}
	if (!InputManager::GetInstance()->GetInputStrength("Fire") && m_bSingleFired)
		m_bSingleFired = false;

	if (InputManager::GetInstance()->GetInputStrength("Reload"))
		ReloadWeapon();
}

void WeaponScript::UpdateStats()
{

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

}

void WeaponScript::RemovePart()
{

}