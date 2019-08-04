#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include <string>
class GunScript : public ScriptComponent
{
public:
	enum eFIRE_TYPES
	{
		SEMI_AUTO,
		FULL_AUTO,
		CHARGE,
	};
private:
	const GameObject* m_Bullet;;
	float m_fTimer;
	const float m_fFireRate;
	GameObject* m_Player;
	GameObject* m_Smoke;
	//bool m_bSemi;
	eFIRE_TYPES m_eFireType;
	int m_iNumClips;
	int m_iClipAmmo;
	const int m_iClipAmmoMax;
	const int m_iMaxClip;
	bool m_bTriggerDown;

	float m_fChargeTime;
	float m_fMaxChargeTime;
	float m_fMinChargeTime;
	float m_fBulletSpeed;
	float m_fMaxScale;
	float m_fRecoil;
public:
	GunScript(GameObject* bullet, const float fFireRate, eFIRE_TYPES eFireType, GameObject* smoke, float speed, int ClipAmmo, int maxclips);
	~GunScript();
	virtual ComponentBase* Clone()
	{
		return new GunScript(*this);
	}
	virtual void Start() override;
	virtual void Update(double dt) override;
	void Fire(Vector3 vDir);
	void PullTrigger(Vector3 vDir, double dt);
	void Reload();
	void ReleaseTrigger(Vector3 vDir);
	void RefillAmmo();
	void SetRecoil(float f);
};
