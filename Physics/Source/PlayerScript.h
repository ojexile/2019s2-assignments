#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
class PlayerScript : public ScriptComponent
{
private:
public:
	PlayerScript();
	~PlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;
};
