#pragma once
#include "Component.h"
#include "Camera.h"
class CameraComponent :
	public Component
{
public:
	enum eCameraTypes
	{
		CAM_NONE,
		CAM_FIRST,
		CAM_ORTHO,
		CAM_CUSTOM_PERSPECT,
		CAM_CUSTOM_ORTHO,
	};
private:
	eCameraTypes m_eCameraType;
	Camera m_Camera;
	bool m_bUseFloatYaw;
public:
	CameraComponent();
	virtual ~CameraComponent();
	virtual Component* Clone()
	{
		return new CameraComponent(*this);
	}

	virtual void Update(double dt) override;
	Camera* GetCamera();
	void SetCameraType(eCameraTypes eCameratype);
	eCameraTypes GetCameraType();

	void SetMouseUseFloatYaw(bool b);
};
