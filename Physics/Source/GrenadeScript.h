#pragma once
#include "ProjectileScript.h"

/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
 Script to handle Grenade behaviour (Explosion, cooking)
/*!
/********************************************************************************/

class GrenadeScript : public ProjectileScript
{
public:
	GrenadeScript(float Lifespan = 1.0, float Damage = 10., float ExplosionRadius = 5.);
	virtual ~GrenadeScript();

	void Update(double deltaTime) override;
	virtual void Collide(GameObject*) override;

	void PullPin(void);
	void ThrowGrenade(const Vector3& dir, const GameObject* GrenadeRef, const float deltaTime);

	virtual Component* Clone() { return new GrenadeScript(*this); }

	void Explode(void);
private:

	float m_fExplosionRadius;

	float m_fExplosionDamage;

	int m_iGrenadeCount;

	bool m_bIsGrenadeCooking;
	bool m_bHasExploded;
};
