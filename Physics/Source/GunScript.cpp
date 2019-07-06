#include "GunScript.h"
#include "BulletScript.h"

GunScript::GunScript(GameObject* bullet, GameObject* player)
	:m_Player(player)
{
	m_Bullet = bullet;
	m_fTimer = 0;
	m_fFireRate = 0.5f;
	m_bSemi = true;

	m_bTriggerDown = false;
}

GunScript::~GunScript()
{
}

void GunScript::Update(double dt)
{
	m_fTimer += (float)dt;
}

void GunScript::PullTrigger(Vector3 vDir)
{
	if (m_fTimer >= m_fFireRate && !m_bTriggerDown)
	{
		Vector3 pos = m_Player->GetComponent<TransformComponent>()->GetPosition();
		GameObject* bul = Instantiate(m_Bullet, pos);
		bul->GetComponent<BulletScript>()->SetDirection(vDir);
		m_fTimer = 0;
	}
	m_bTriggerDown = true;
}
void GunScript::ReleaseTrigger()
{
	m_bTriggerDown = false;
}