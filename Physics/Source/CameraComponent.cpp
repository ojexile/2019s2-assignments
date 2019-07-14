#include "CameraComponent.h"
#include "Application.h"

CameraComponent::CameraComponent()
{
	m_eCameraType = CAM_NONE;
	m_Camera.Init(Vector3(0, 0, 0), Vector3(0, 1, 0));
}

CameraComponent::~CameraComponent()
{
}

Camera* CameraComponent::GetCamera()
{
	return &m_Camera;
}

void CameraComponent::Update(double dt)
{
	TransformComponent* Trans = GetComponent<TransformComponent>();
	Vector3 vPos = Trans->GetPosition();
	m_Camera.UpdateView(dt, vPos);
}
void CameraComponent::SetCameraType(eCameraTypes eCameratype)
{
	m_eCameraType = eCameratype;
}
CameraComponent::eCameraTypes CameraComponent::GetCameraType()
{
	return m_eCameraType;
}