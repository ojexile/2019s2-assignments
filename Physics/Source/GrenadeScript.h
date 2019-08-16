#pragma once
#include "ProjectileScript.h"
class GrenadeScript : public ProjectileScript
{
public:
	GrenadeScript(double Lifespan = 1.0, double Damage = 10., float ExplosionRadius = 5.);
	virtual ~GrenadeScript();

	void Update(double deltaTime) override;
	virtual void Collide(GameObject*) override;

	void PullPin(void);
	void ThrowGrenade(const Vector3& dir, const GameObject* GrenadeRef, const double deltaTime);

	virtual ComponentBase* Clone() { return new GrenadeScript(*this); }

	void Explode(void);
private:

	float m_fExplosionRadius;
	bool m_bIsGrenadeCooking;
};

