#pragma once
#include "ScriptComponent.h"
class BulletScript : public ScriptComponent
{
private:
	Vector3 m_vDir;
public:
	BulletScript();
	~BulletScript();
	virtual ComponentBase* Clone()
	{
		return new BulletScript(*this);
	}

	void SetDirection(Vector3 vDir);
	void Update(double dt) override;
};

