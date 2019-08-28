#pragma once
#include "Augment.h"
#include "GameObject.h"

#include <vector>
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
	ProjectileScript(float Lifespan = 3.0, float Damage = 10.);
	virtual ~ProjectileScript();

	void Update(double deltaTime) override;

	virtual Component* Clone() { return new ProjectileScript(*this); }
	virtual void Collide(GameObject*) override;

	void AddAugment(Augment* aug);

	bool ActivateEffects(ProjectileScript* proj, GameObject* go);

	float GetDamage();
	float GetLifespan();

	void SetDamage(float Damage);
	void SetLifespan(float Lifespan);

protected:
	float m_fDamage;
	float m_fLifespan;
	bool m_bIsAugmented;
	std::vector<Augment*> m_AugmentList;
};
