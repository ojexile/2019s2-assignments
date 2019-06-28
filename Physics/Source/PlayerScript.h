#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
class PlayerScript : public ScriptComponent
{
private:
	Vector3* m_vCameraFront;
	Vector3* m_vCameraUp;
public:
	PlayerScript();
	~PlayerScript();

	void Update(double dt) override;
	virtual void Start() override;
};
