#pragma once
#include "ScriptComponent.h"
/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
Script to handle general Projectile Behaviour.
/*!
/********************************************************************************/
class ProjectileScript : public ScriptComponent
{
public:
	ProjectileScript(float Lifespan = 1.0, float Damage = 10.);
	virtual ~ProjectileScript();

	void Update(double deltaTime) override;

	virtual Component* Clone() { return new ProjectileScript(*this); }
	virtual void Collide(GameObject*) override;

	float getDamage();
	float getLifespan();

protected:
	float m_fDamage;
	float m_fLifespan;
};
