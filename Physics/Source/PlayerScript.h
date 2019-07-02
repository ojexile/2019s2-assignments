#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
class PlayerScript : public ScriptComponent
{
private:
public:
	PlayerScript();
	~PlayerScript();

	void Update(double dt) override;
	virtual void Start() override;
};
