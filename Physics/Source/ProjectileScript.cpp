#include "ProjectileScript.h"



ProjectileScript::ProjectileScript()
	: m_fLifespan(1.f)
{
}


ProjectileScript::~ProjectileScript()
{
}

void ProjectileScript::Update(double deltaTime)
{
	if (m_fLifespan >= 0.f)
		m_fLifespan = m_fLifespan - deltaTime;
	else
		DestroySelf();
}

double ProjectileScript::getDamage()
{
	return m_fDamage;
}

double ProjectileScript::getLifespan()
{
	return m_fLifespan;
}