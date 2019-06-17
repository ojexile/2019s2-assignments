#pragma once
#include "ComponentBase.h"

#include "Camera.h"
class CameraComponent :
	public ComponentBase
{
private:
	Camera m_Camera;
public:
	CameraComponent();
	virtual ~CameraComponent();

	virtual void Update(double dt) override;
	Camera* GetCamera();
};
