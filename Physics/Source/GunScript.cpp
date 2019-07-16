#include "GunScript.h"
#include "BulletScript.h"
#include "ChengRigidbody.h"
GunScript::GunScript(GameObject* bullet, GameObject* player, const float fFireRate, bool bSemi)
	:m_Player(player)
	, m_bSemi(bSemi)
	, m_fFireRate(fFireRate)
{
	m_Bullet = bullet;
	m_fTimer = 0;
	m_iClipAmmo = 3;
	m_iNumClips = 2;
	m_iClipAmmoMax = 20;
	m_bTriggerDown = false;
}

GunScript::~GunScript()
{
}

void GunScript::Update(double dt)
{
	m_fTimer += (float)dt;
}
void GunScript::Fire(Vector3 vDir)
{
	if (m_iClipAmmo <= 0)
		return;
	float fBallSpeed = 120.f;
	Vector3 ballDir = vDir;
	Vector3 pos = m_Player->GetComponent<TransformComponent>()->GetPosition();
	GameObject* bul = Instantiate(m_Bullet, pos);
	if (!bul)
		return;
	bul->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	--m_iClipAmmo;
	m_fTimer = 0;
}
void GunScript::PullTrigger(Vector3 vDir)
{
	if (m_fTimer >= m_fFireRate)
	{
		if (m_bSemi)
		{
			if (!m_bTriggerDown)
				Fire(vDir);
		}
		else
			Fire(vDir);
	}

	m_bTriggerDown = true;
}
void GunScript::Reload()
{
	if (m_iNumClips <= 0)
		return;
	m_iClipAmmo = m_iClipAmmoMax;
	--m_iNumClips;
}
void GunScript::ReleaseTrigger()
{
	m_bTriggerDown = false;
}