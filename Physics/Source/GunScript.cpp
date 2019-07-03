#include "GunScript.h"
#include "BulletScript.h"


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

void GunScript::Shoot(Vector3 vDir)
{
	if (m_fTimer >= m_fFireRate)
	{
		GameObject* bul = Instantiate(m_sBullet, GetComponent<TransformComponent>()->GetPosition());
		bul->GetComponent<BulletScript>()->SetDirection(vDir);
		m_fTimer = 0;
	}
}