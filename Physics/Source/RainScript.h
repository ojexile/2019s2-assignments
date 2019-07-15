#pragma once
#include "ScriptComponent.h"
class RainScript :
	public ScriptComponent
{
private:
	GameObject* m_BounceParticle;
public:
	RainScript(GameObject* BounceParticle);
	virtual ~RainScript();
	virtual ComponentBase* Clone()
	{
		return new RainScript(*this);
	}

	void Update(double dt) override;
};
