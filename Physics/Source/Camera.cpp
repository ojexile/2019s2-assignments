#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{

	Reset();
	m_fCamSpeed = 5;
	m_fPitch = 0;
	m_fYaw = 0;
	m_bIsFirstMouseMove = true;
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& target, const Vector3& up)
{
	this->m_vTarget = target;
	this->m_vUp = up;
}

void Camera::Reset()
{
	m_vTarget.Set(0, 0, 0);
	m_vUp.Set(0, 1, 0);
}

void Camera::Update(double dt)
{

}
void Camera::UpdateFirstPersonView(double dt, Vector3 vPos)
{
	if (m_fPitch > 80.0f)
		m_fPitch = 80.0f;
	if (m_fPitch < -80.0f)
		m_fPitch = -80.0f;

	m_vTarget.x = cos(Math::DegreeToRadian(m_fPitch)) * cos(Math::DegreeToRadian(m_fYaw));
	m_vTarget.y = sin(Math::DegreeToRadian(m_fPitch));
	m_vTarget.z = cos(Math::DegreeToRadian(m_fPitch)) * sin(Math::DegreeToRadian(m_fYaw));
	m_vTarget.Normalize();

}
void Camera::UpdateYawPitchMouse(float xpos, float ypos)
{
	if (m_bIsFirstMouseMove)
	{
		m_fLastX = xpos;
		m_fLastY = ypos;
		m_bIsFirstMouseMove = false;
	}

	float xoffset = xpos - m_fLastX;
	float yoffset = m_fLastY - ypos;
	m_fLastX = xpos;
	m_fLastY = ypos;

	xoffset *= this->m_fCamSpeed;
	yoffset *= this->m_fCamSpeed;

	m_fYaw += xoffset;
	m_fPitch += yoffset;
}	
