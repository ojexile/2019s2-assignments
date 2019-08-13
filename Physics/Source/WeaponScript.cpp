#include "WeaponScript.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "TransformComponent.h"

WeaponScript::WeaponScript(GameObject* Projectile, int iBulletsFiredCount, int iMagazineRounds, int iMagazineRounds_Max, int iAmmo, int iAmmo_Max, float fFirerate, float fBulletSpread, float fBulletForce, FIRING_MODE FiringMode)
	: m_iBulletsFiredCount(iBulletsFiredCount),
	  m_iMagazineRounds(iMagazineRounds),
	  m_iMagazineRounds_Max(iMagazineRounds_Max),
	  m_iAmmo(iAmmo),
	  m_iAmmo_Max(m_iAmmo_Max),
	  m_fFirerate(fFirerate),
	  m_fBulletSpread(fBulletSpread),
	  m_fBulletForce (fBulletForce),
	  m_Projectile(Projectile),
	  m_FiringMode(FiringMode)
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

void WeaponScript::PullTrigger(const Vector3& dir)
{

}

void WeaponScript::ReleaseTrigger()
{

}

void WeaponScript::Update(double deltaTime)
{
	if (InputManager::GetInstance()->GetInputStrength("Fire"))
	{
		FireWeapon(Vector3(0,1,0));
	}
}

void WeaponScript::UpdateStats()
{

}

void WeaponScript::FireWeapon(const Vector3& dir)
{
	if (!m_Projectile)
	{
		std::cout << "Can't Fire";
		return;
	}
	
	GameObject* bullet = Instantiate(m_Projectile, this->GetPosition());
	bullet->RIGID->AddForce(m_fBulletForce * dir);
	bullet->RIGID->SetAffectedByGravity(false);
}

void WeaponScript::ReloadWeapon(void)
{

}

void WeaponScript::AddPart(GameObject* part)
{

}

void WeaponScript::RemovePart()
{

}