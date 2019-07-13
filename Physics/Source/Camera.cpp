#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{
	Reset();
	m_fCamSpeed = 0.2f;
	m_fPitch = 0;
	m_fYaw = 270;
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

	m_vDir.x = cos(Math::DegreeToRadian(m_fPitch)) * cos(Math::DegreeToRadian(m_fYaw));
	m_vDir.y = sin(Math::DegreeToRadian(m_fPitch));
	m_vDir.z = cos(Math::DegreeToRadian(m_fPitch)) * sin(Math::DegreeToRadian(m_fYaw));

	/*const float speed = 1000.f * (float)dt;
	if (Application::IsKeyPressed(VK_LEFT))
	{
		m_fYaw -= speed * (float)dt;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		m_fYaw += speed * (float)dt;
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		m_fPitch += speed * (float)dt;
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		m_fPitch -= speed * (float)dt;
	}*/
	m_vTarget = vPos + m_vDir;
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

	// TODO camera movement bound to frame rate not time
	xoffset *= this->m_fCamSpeed;
	yoffset *= this->m_fCamSpeed;

	m_fYaw += xoffset;
	m_fPitch += yoffset;
}
// Getters
Vector3 Camera::GetTarget()
{
	return m_vTarget;
}
Vector3 Camera::GetUp()
{
	return m_vUp;
}
Vector3 Camera::GetDir()
{
	return m_vDir;
}
void Camera::SetDir(Vector3 v)
{
	m_vDir = v;
}