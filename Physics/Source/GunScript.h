#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include "WeaponPartScript.h"

#include <vector>

/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
 Script to handle weapon behaviours such as Firing, Shooting, Reloading
	   etc.
/*!
/********************************************************************************/
class GunScript : public ScriptComponent
{
public:

	enum FIRING_MODE
	{
		SINGLE,
		AUTO
	};

	GunScript(GameObject* Projectile, int iBulletsFiredCount = 1, int iMagazineRounds = 8,
		int iMagazineRounds_Max = 8, float fReloadTimeBuffer = 1.2f, float fFirerate = 0.75f,
		float fBulletSpread = 0.5f, float fBulletForce = 5.f, FIRING_MODE FiringMode = AUTO);
	~GunScript();

	//Interface Functions
	void PullTrigger(const Vector3& dir, const double deltaTime);
	void ReleaseTrigger();
	void ReloadWeapon(void);

	void Update(double deltaTime) override;
	void UpdateStats(GameObject* go, bool Multiply);

	void EquipPart(GameObject* part, WeaponPartScript::SLOT_TYPE slot);
	void SetBulletsFired(int BulletsFired);
	void SetMagazineRounds(int MagRounds);
	void SetMaxMagazineRounds(int MagRounds_Max);
	void SetFireRate(float FireRate);
	void SetBulletSpread(float BulletSpread);
	void SetReloadTime(float ReloadBufferTime);

	int GetBulletsFired();
	int GetMagazineRounds();
	int GetMaxMagazineRounds();
	float GetFireRate();
	float GetBulletSpread();
	float GetReloadTime();
	float GetReloadElapsedTime();
	bool IsReloading();
	GameObject* GetBullet();

	virtual Component* Clone() { return new GunScript(*this); }

private:

	void FireWeapon(const Vector3& dir, const double deltaTime);
	void ApplyAugmentOnBullet(std::vector<GameObject*>& m_vector, GameObject* go);
	void DestroyPart(std::vector<GameObject*>& m_Updatedvector, GameObject* go);
	void DamageEquippedParts(std::vector<GameObject*>& m_vector, const double deltaTime);

	int m_iBulletsFiredCount;

	int m_iMagazineRounds;
	int m_iMagazineRounds_Max;

	float m_fFirerate;
	float m_fBufferTime;

	float m_fBulletForce;
	float m_fBulletSpread;

	float m_fReloadElapsedTime;
	float m_fReloadTime;

	bool m_bSingleFired;
	bool m_bIsReloading;

	enum FIRING_MODE m_FiringMode;

	GameObject* m_Projectile;

	std::vector<GameObject*> m_ScopeParts;
	std::vector<GameObject*> m_MuzzleParts;
	std::vector<GameObject*> m_GripParts;
	std::vector<GameObject*> m_StockParts;
};
