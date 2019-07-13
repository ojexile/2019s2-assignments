#pragma once
#include "ScriptComponent.h"
class BallScript :
	public ScriptComponent
{
private:
	float m_fLastPopSoundTime;
public:
	BallScript();
	virtual ~BallScript();
	virtual ComponentBase* Clone()
	{
		return new BallScript(*this);
	}

	virtual void Collide(GameObject* go) override;
};
