#include "GunScript.h"



GunScript::GunScript(std::string bullet)
{
	m_sBullet = bullet;
	m_fTimer = 0;
	m_fFireRate = 0.5f;
}


GunScript::~GunScript()
{
}


void GunScript::Update(double dt)
{
	m_fTimer += dt;
}

void GunScript::Shoot()
{
	if (m_fTimer >= m_fFireRate)
	{
		Instantiate(m_sBullet, GetComponent<TransformComponent>()->GetPosition());
	}
}