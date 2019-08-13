#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include "PartScript.h"

#include <queue>

/********************************************************************************
Author: Ryan Tan Zheng Rong
Brief: Script to handle weapon behaviours such as Firing, Shooting, Reloading
	   etc.
********************************************************************************/

class WeaponScript : public ScriptComponent
{
public:

	enum FIRING_MODE
	{
		SINGLE,
		AUTO
	};

	WeaponScript(GameObject* Projectile, int iBulletsFiredCount = 1, int iMagazineRounds = 8, int iMagazineRounds_Max = 8, int iAmmo = 100, int iAmmo_Max = 100, float fFirerate = 0.333f, float fBulletSpread = 1.f, float fBulletForce = 100.f, FIRING_MODE FiringMode = AUTO);
	~WeaponScript();

	//Interface Functions
	void PullTrigger(const Vector3& dir, const double deltaTime);
	void ReleaseTrigger();

	void Update(double deltaTime) override;
	void UpdateStats();

	virtual WeaponScript* Clone() { return new WeaponScript(*this); }

private:

	void FireWeapon(const Vector3& dir, const double deltaTime);
	void ReloadWeapon(void);

	void AddPart(GameObject* part);
	void RemovePart();

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

	std::queue<PartScript*>	m_ScopeParts;
	std::queue<PartScript*> m_MuzzleParts;
	std::queue<PartScript*> m_GripParts;
	std::queue<PartScript*> m_StockParts;

};

