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

	void Update(double dt) override;
	void Shoot();
};

