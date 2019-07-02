#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
class ChengPlayerScript : public ScriptComponent
{
private:
	Vector3* m_vCameraFront;
	Vector3* m_vCameraUp;
public:
	ChengPlayerScript();
	~ChengPlayerScript();

	void Update(double dt) override;
	virtual void Start() override;
};
