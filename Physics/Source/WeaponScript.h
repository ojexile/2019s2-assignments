#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include "PartScript.h"

#include <vector>

/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
 Script to handle weapon behaviours such as Firing, Shooting, Reloading
	   etc.
/*!
/********************************************************************************/
class WeaponScript : public ScriptComponent
{
public:

	enum FIRING_MODE
	{
		SINGLE,
		AUTO
	};

	WeaponScript(GameObject* Projectile, int iBulletsFiredCount = 1, int iMagazineRounds = 8, int iMagazineRounds_Max = 8, int iAmmo = 100, int iAmmo_Max = 100, float fFirerate = 0.250f, float fBulletSpread = 0.35f, float fBulletForce = 20.f, FIRING_MODE FiringMode = AUTO);
	~WeaponScript();

	//Interface Functions
	void PullTrigger(const Vector3& dir, const double deltaTime);
	void ReleaseTrigger();

	void Update(double deltaTime) override;
	void UpdateStats(GameObject* go, bool Multiply);

	void EquipPart(GameObject* part);

	void SetAmmo(int Ammo);
	void SetMaxAmmo(int Ammo_Max);
	void SetBulletsFired(int BulletsFired);
	void SetMagazineRounds(int MagRounds);
	void SetMaxMagazineRounds(int MagRounds_Max);
	void SetFireRate(float FireRate);
	void SetBulletSpread(float BulletSpread);

	int GetAmmo();
	int GetMaxAmmo();
	int GetBulletsFired();
	int GetMagazineRounds();
	int GetMaxMagazineRounds();
	float GetFireRate();
	float GetBulletSpread();

	virtual Component* Clone() { return new WeaponScript(*this); }

private:

	void FireWeapon(const Vector3& dir, const double deltaTime);
	void ReloadWeapon(void);

	void DestroyPart(std::vector<GameObject*>& m_Updatedvector, GameObject* go);

	void DamageEquippedParts(std::vector<GameObject*>& m_vector, const double deltaTime);

	int m_iBulletsFiredCount;

	int m_iMagazineRounds;
	int m_iMagazineRounds_Max;

	int m_iAmmo; //Current amount of bullets held
	int m_iAmmo_Max; //Max Capacity of Ammo held by weapon

	float m_fFirerate;
	float m_fBufferTime;

	float m_fBulletForce;
	float m_fBulletSpread;

	bool m_bSingleFired;

	enum FIRING_MODE m_FiringMode;

	GameObject* m_Projectile;

	std::vector<GameObject*> m_ScopeParts;
	std::vector<GameObject*> m_MuzzleParts;
	std::vector<GameObject*> m_GripParts;
	std::vector<GameObject*> m_StockParts;
};
