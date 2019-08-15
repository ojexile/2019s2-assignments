#pragma once
#include "ScriptComponent.h"
class ProjectileScript : public ScriptComponent
{
public:
	ProjectileScript(double Lifespan = 1.0, double Damage = 10.);
	virtual ~ProjectileScript();

	void Update(double deltaTime) override;

	virtual ComponentBase* Clone() { return new ProjectileScript(*this); }
	virtual void Collide(GameObject*) override;

	double getDamage();
	double getLifespan();

protected:
	double m_dDamage;
	double m_dLifespan;
};

