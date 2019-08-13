#pragma once
#include "ComponentBase.h"
#include "TransformComponent.h"
#include "Camera.h"
class CameraComponent :
	public ComponentBase
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
	virtual ComponentBase* Clone()
	{
		return new CameraComponent(*this);
	}

	virtual void Update(double dt) override;
	Camera* GetCamera();
	void SetCameraType(eCameraTypes eCameratype);
	eCameraTypes GetCameraType();

	void SetMouseUseFloatYaw(bool b);
};
