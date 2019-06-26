#pragma once
#include "ComponentBase.h"

#include "Camera.h"
class CameraComponent :
	public ComponentBase
{
public:
	enum eCameraTypes
	{
		CAM_NONE,
		CAM_FIRST,
		CAM_THIRD,
		CAM_CUSTOM,
	};
private:
	eCameraTypes m_eCameraType;
	Camera m_Camera;
public:
	CameraComponent();
	virtual ~CameraComponent();

	virtual void Update(double dt) override;
	Camera* GetCamera();
	void SetCameraType(eCameraTypes eCameratype);
};
