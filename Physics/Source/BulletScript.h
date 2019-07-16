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
	~BulletScript();
	virtual ComponentBase* Clone()
	{
		return new BulletScript(*this);
	}

	void Update(double dt) override;
};
