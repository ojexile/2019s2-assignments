#pragma once
#include "ScriptComponent.h"
class BulletScript : public ScriptComponent
{
private:
	Vector3 m_vDir;
	const float m_fLifeTime;
	float m_fCurrentLife;
public:
	BulletScript(const float fLifeTime);
	~BulletScript();
	virtual ComponentBase* Clone()
	{
		return new BulletScript(*this);
	}

	void SetDirection(Vector3 vDir);
	void Update(double dt) override;
};
