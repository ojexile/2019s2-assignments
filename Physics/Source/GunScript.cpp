#include "GunScript.h"
#include "BulletScript.h"
#include "ChengRigidbody.h"
#include "Application.h"
#include "SceneManager.h"
#include "ChengPlayerScript.h"
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
	m_bIsHolding = false;
	myaw = 0;
	mpitch = 0;
}

GunScript::~GunScript()
{
	//delete m_Smoke;
	//delete m_Bullet;
}
void GunScript::Start()
{
	this->m_Player = GetCameraGO();
}
float Lerp(float Start, float Target, float Rate)
{
	if (Start > Target)
	{
		float out = Start + -Rate;
		if (out < Target)
			return Target;
		else
			return out;
	}
	if (Start < Target)
	{
		float out = Start + Rate;
		if (out > Target)
			return Target;
		else
			return out;
	}
	return 0;
}
void GunScript::Update(double dt)
{
	m_fTimer += (float)dt;

	if (myaw != 0 || mpitch != 0)
	{
		float yaw = Lerp(GetCamera()->GetYaw(), myaw, m_fRecoil / 15);
		float pitch = Lerp(GetCamera()->GetPitch(), mpitch, m_fRecoil / 15);
		GetCamera()->SetDir(yaw, pitch);
		if (yaw == myaw)
			myaw = 0;
		if (pitch == mpitch)
			mpitch = 0;
	}
}

void GunScript::Fire(Vector3 vDir)
{
	if (m_eFireType == CHARGE)
	{
		if (m_fChargeTime < m_fMinChargeTime)
			return;
	}
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
	myaw = Math::RandFloatMinMax(-m_fRecoil / 5, m_fRecoil / 5) + GetCamera()->GetYaw();
	mpitch = Math::RandFloatMinMax(-m_fRecoil, m_fRecoil) + GetCamera()->GetPitch();

	// GetCamera()->Get(yaw, pitch);
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
void GunScript::SetHolding(bool b)
{
	m_bIsHolding = b;
}
bool GunScript::GetHolding()
{
	return m_bIsHolding;
}
bool GunScript::IsEmpty()
{
	// no ammo
	if (m_iClipAmmo <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}