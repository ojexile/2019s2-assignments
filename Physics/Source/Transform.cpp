#include "Transform.h"

Transform::Transform()
{
	m_vPosition = { 0,0,0 };
	m_vRotation = { 0,0,0 };
	m_vScale = { 1,1,1 };
}

Transform::~Transform()
{
}

void Transform::Update(double dt)
{
}
Vector3 Transform::GetPosition()
{
	return m_vPosition;
}
Vector3 Transform::GetRotation()
{
	return m_vRotation;
}
Vector3 Transform::GetScale()
{
	return m_vScale;
}

void Transform::SetPosition(Vector3 pos)
{
	m_vPosition = pos;
}
void Transform::SetPosition(float x, float y, float z)
{
	m_vPosition = { x,y,z };
}