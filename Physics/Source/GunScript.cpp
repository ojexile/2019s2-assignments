#include "GunScript.h"
#include "BulletScript.h"
#include "ChengRigidbody.h"
GunScript::GunScript(GameObject* bullet, GameObject* player, const float fFireRate, eFIRE_TYPES eFireType)
	: m_Player(player)
	, m_eFireType(eFireType)
	, m_fFireRate(fFireRate)
{
	m_Bullet = bullet;
	m_fTimer = 0;
	m_iClipAmmo = 3;
	m_iNumClips = 2;
	m_iClipAmmoMax = 20;
	m_bTriggerDown = false;
	m_fChargeTime = 0;
	m_fMaxChargeTime = 3;
	m_fMaxScale = 3;
	m_fMinChargeTime = 0.5f;
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
	float fScale = 1;
	switch (m_eFireType)
	{
	case GunScript::CHARGE:
	{
		if (m_fChargeTime < m_fMinChargeTime)
			return;
		fScale = (m_fChargeTime / m_fMaxChargeTime)* m_fMaxScale;
	}
	break;
	case GunScript::SEMI_AUTO:
		break;
	case GunScript::FULL_AUTO:
		break;
	default:
		break;
	}
	if (m_iClipAmmo <= 0)
		return;
	float fBallSpeed = 120.f;
	Vector3 ballDir = vDir;
	Vector3 pos = m_Player->GetComponent<TransformComponent>()->GetPosition();
	GameObject* bul = Instantiate(m_Bullet, pos);
	if (!bul)
		return;
	bul->GetComponent<TransformComponent>()->SetScale(fScale, fScale, fScale);
	bul->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	--m_iClipAmmo;
	m_fTimer = 0;
}
void GunScript::PullTrigger(Vector3 vDir, double dt)
{
	if (m_fTimer >= m_fFireRate)
	{
		const float ChargeRate = 1.f;
		switch (m_eFireType)
		{
		case GunScript::SEMI_AUTO:
		{
			if (!m_bTriggerDown)
				Fire(vDir);
		}
		break;
		case GunScript::FULL_AUTO:
			Fire(vDir);
			break;
		case GunScript::CHARGE:
			m_fChargeTime += (float)dt;
			break;
		default:
			break;
		}
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
void GunScript::ReleaseTrigger(Vector3 vDir)
{
	if (m_eFireType == CHARGE)
	{
		Fire(vDir);
		m_fChargeTime = 0;
	}
	m_bTriggerDown = false;
}