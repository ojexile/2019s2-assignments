#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include <string>
class GunScript : public ScriptComponent
{
private:
	std::string m_sBullet;;
	float m_fTimer;
	float m_fFireRate;
public:
	GunScript(std::string bullet);
	~GunScript();
	virtual ComponentBase* Clone()
	{
		return new GunScript(*this);
	}

	void Update(double dt) override;
	void Shoot();
};

