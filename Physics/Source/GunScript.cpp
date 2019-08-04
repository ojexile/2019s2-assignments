#include "GunScript.h"
#include "BulletScript.h"
#include "ChengRigidbody.h"
#include "Application.h"
#include "SceneManager.h"
GunScript::GunScript(GameObject* bullet, const float fFireRate, eFIRE_TYPES eFireType, GameObject* smoke, float speed, int ClipAmmo, int maxclips)
	: m_eFireType(eFireType)
	, m_fFireRate(fFireRate)
	, m_Smoke(smoke)
	, m_fBulletSpeed(speed)
	, m_iClipAmmoMax(ClipAmmo)
	, m_iMaxClip(maxclips)
	, m_Bullet(bullet)
{
	m_iClipAmmo = m_iClipAmmoMax;
	m_iNumClips = maxclips;

	m_fTimer = 0;
	m_bTriggerDown = false;
	m_fChargeTime = 0;
	m_fMaxChargeTime = 3;
	m_fMaxScale = 7;
	m_fMinChargeTime = 0.01f;
}

GunScript::~GunScript()
{
}
void GunScript::Start()
{
	this->m_Player = GetCameraGO();
}
//bool trigger = false;
void GunScript::Update(double dt)
{
	m_fTimer += (float)dt;
	// no ammo
	if (m_iClipAmmo <= 0)
	{
		GetComponent<TransformComponent>()->SetRotation(45, 0, 0, 1);
	}
	else
	{
		GetComponent<TransformComponent>()->SetRotation(0, 0, 0, 1);
	}
}
void GunScript::Fire(Vector3 vDir)
{

	if (m_iClipAmmo <= 0)
		return;
	Vector3 ballDir = vDir;
	Vector3 pos = m_Player->GetComponent<TransformComponent>()->GetPosition();
	Instantiate(m_Smoke, pos + vDir * 2);
	GameObject* bul = Instantiate(m_Bullet, pos);
	if (!bul)
		return;
	switch (m_eFireType)
	{
	case GunScript::CHARGE:
	{
		if (m_fChargeTime < m_fMinChargeTime)
			return;
		float fScale = 1;
		fScale = (m_fChargeTime / m_fMaxChargeTime) * m_fMaxScale;
		fScale = Math::Clamp(fScale, 2.f, m_fMaxScale);
		bul->GetComponent<TransformComponent>()->SetScale(fScale, fScale, fScale);
		bul->GetComponent<ChengRigidbody>()->SetMass(fScale);
	}
	break;
	case GunScript::SEMI_AUTO:
		break;
	case GunScript::FULL_AUTO:
		break;
	default:
		break;
	}
	bul->GetComponent<ChengRigidbody>()->SetVel(m_fBulletSpeed * ballDir);
	--m_iClipAmmo;
	m_fTimer = 0;
	// Recoil
	float yaw = Math::RandFloatMinMax(-m_fRecoil, m_fRecoil);
	float pitch = Math::RandFloatMinMax(-m_fRecoil, m_fRecoil);
	GetCamera()->OffsetDir(yaw, pitch);
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
void GunScript::RefillAmmo()
{
	m_iNumClips = m_iMaxClip;
}
void GunScript::SetRecoil(float f)
{
	m_fRecoil = f;
}