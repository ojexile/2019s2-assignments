#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	m_eCameraType = CAM_NONE;
	m_Camera.Init( Vector3(0, 0, 0), Vector3(0, 1, 0));
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
	Vector3 vPos = GetComponent<Transform>()->GetPosition();
	switch (m_eCameraType)
	{
	case CameraComponent::CAM_NONE:
		break;
	case CameraComponent::CAM_FIRST:
		m_Camera.UpdateFirstPersonView(dt, vPos);
		break;
	case CameraComponent::CAM_THIRD:
		break;
	case CameraComponent::CAM_CUSTOM:
		break;
	default:
		break;
	}

	//float speed{ 2.f };
	////Temp movement
	//if (KeyInput::getInstance()->isKeyPressed(K_W))
	//{
	//	this->m_v3Position += this->m_v3Front * speed;
	//}
	//if (KeyInput::getInstance()->isKeyPressed(K_A))
	//{
	//	this->m_v3Position -= this->m_v3Right *speed;
	//}
	//if (KeyInput::getInstance()->isKeyPressed(K_D))
	//{
	//	this->m_v3Position += this->m_v3Right *speed;
	//}
	//if (KeyInput::getInstance()->isKeyPressed(K_S))
	//{
	//	this->m_v3Position -= this->m_v3Front *speed;
	//}
}
void CameraComponent::SetCameraType(eCameraTypes eCameratype)
{
	m_eCameraType = eCameratype;
}
