#include "GunScript.h"
#include "BulletScript.h"
#include "ChengRigidbody.h"
#include "Application.h"
GunScript::GunScript(GameObject* bullet, GameObject* player, const float fFireRate, eFIRE_TYPES eFireType)
	: m_Player(player)
	, m_eFireType(eFireType)
	, m_fFireRate(fFireRate)
{
	m_Bullet = bullet;
	m_fTimer = 0;
	m_iClipAmmo = 5;
	//m_iNumClips = 3;
	m_iNumClips = 20000;
	m_iClipAmmoMax = 5;
	m_bTriggerDown = false;
	m_fChargeTime = 0;
	m_fMaxChargeTime = 3;
	m_fMaxScale = 7;
	m_fMinChargeTime = 0.01f;
}

GunScript::~GunScript()
{
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

	//if (Application::IsMousePressed(1) && !trigger)
	//{
	//	trigger = true;
	//	float fScale = 2;
	//	float fBallSpeed = 120.f;
	//	//Vector3 ballDir = {};
	//	double x, y;
	//	Application::GetCursorPos(&x, &y);
	//	float posx = (float)x / Application::GetWindowWidth() * 300 - 150;
	//	float posz = (float)y / Application::GetWindowHeight() * 300 - 150;

	//	Vector3 pos = { posx, 10, posz };
	//	GameObject* bul = Instantiate(m_Bullet, pos);
	//	if (!bul)
	//		return;
	//	bul->GetComponent<TransformComponent>()->SetScale(fScale, fScale, fScale);
	//	//bul->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	//	bul->GetComponent<ChengRigidbody>()->SetMass(fScale);
	//	--m_iClipAmmo;
	//	m_fTimer = 0;
	//}
	//if (!Application::IsMousePressed(1))
	//{
	//	trigger = false;
	//}
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
		fScale = (m_fChargeTime / m_fMaxChargeTime) * m_fMaxScale;
		fScale = Math::Clamp(fScale, 2.f, m_fMaxScale);
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
	//pos.y = 10;
	GameObject* bul = Instantiate(m_Bullet, pos);
	if (!bul)
		return;
	bul->GetComponent<TransformComponent>()->SetScale(fScale, fScale, fScale);
	bul->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
	bul->GetComponent<ChengRigidbody>()->SetMass(fScale);
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