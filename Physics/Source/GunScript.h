#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include <string>
class GunScript : public ScriptComponent
{
private:
	GameObject* m_Bullet;;
	float m_fTimer;
	float m_fFireRate;
	GameObject* m_Player;
	bool m_bSemi;

	bool m_bTriggerDown;
public:
	GunScript(GameObject* bullet, GameObject* player);
	~GunScript();
	virtual ComponentBase* Clone()
	{
		return new GunScript(*this);
	}

	void Update(double dt) override;
	void PullTrigger(Vector3 vDir);
	void ReleaseTrigger();
};
