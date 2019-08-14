#pragma once
#include "ScriptComponent.h"
class ProjectileScript : public ScriptComponent
{
public:
	ProjectileScript(double Lifespan = 1.0, double Damage = 10.);
	virtual ~ProjectileScript();

	void Update(double deltaTime) override;

	virtual ProjectileScript* Clone() { return new ProjectileScript(*this); }

	double getDamage();
	double getLifespan();
	virtual void Collide(GameObject*) override;
private:
	double m_dDamage;
	double m_dLifespan;
};

