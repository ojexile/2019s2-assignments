#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	m_Camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update(double dt)
{
}

Camera* CameraComponent::GetCamera()
{
	return &m_Camera;
}