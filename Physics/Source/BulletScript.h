#pragma once
#include "ScriptComponent.h"
class BulletScript : public ScriptComponent
{
private:
	const float m_fLifeTime;
	float m_fCurrentLife;
	float m_fLastPopSoundTime;
public:
	BulletScript(const float fLifeTime);
	virtual ~BulletScript();
	virtual ComponentBase* Clone()
	{
		return new BulletScript(*this);
	}

	virtual void Update(double dt) override;
	virtual void Collide(GameObject* go) override;
};
