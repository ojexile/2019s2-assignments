#pragma once
#include "ScriptComponent.h"
class ProjectileScript : public ScriptComponent
{
public:
	ProjectileScript();
	virtual ~ProjectileScript();

	void Update(double deltaTime) override;

	virtual ProjectileScript* Clone() { return new ProjectileScript(*this); }

	double getDamage();
	double getLifespan();
	virtual void Collide(GameObject*) override;
private:
	double m_fDamage;
	double m_fLifespan;
};

