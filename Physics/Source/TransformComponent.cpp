#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	m_vPosition.SetZero();
	m_vRelativePosition.SetZero();
	m_vRotateAxis.SetZero();
	m_vScale.Set(1, 1, 1);
	m_fdegrees = 0.f;
}

TransformComponent::TransformComponent(Vector3 pos)
{
	m_vPosition.Set(pos.x, pos.y, pos.z);
	m_vRelativePosition.SetZero();
	m_vRotateAxis.SetZero();
	m_vScale.Set(1, 1, 1);
	m_fdegrees = 0.f;
}

TransformComponent::~TransformComponent()
{
}

/*****
Update
******/

void TransformComponent::Update(double dt)
{
}

/***************
Setter functions
***************/

void TransformComponent::SetScale(float scaleX, float scaleY, float scaleZ)
{
	this->m_vScale.Set(scaleX, scaleY, scaleZ);
}

void TransformComponent::SetRotation(float degrees, int xAxis, int yAxis, int zAxis)
{
	this->m_vRotateAxis.Set((float)xAxis, yAxis, zAxis);
	this->m_fdegrees = degrees;
}

void TransformComponent::SetPosition(float translateX, float translateY, float translateZ)
{
	m_vPosition.Set(translateX, translateY, translateZ);
}

void TransformComponent::SetPosition(Vector3 arg)
{
	this->m_vPosition = arg;
}
void TransformComponent::SetRelativePosition(float translateX, float translateY, float translateZ)
{
	m_vRelativePosition.Set(translateX, translateY, translateZ);
}

void TransformComponent::SetRelativePosition(Vector3 arg)
{
	this->m_vRelativePosition = arg;
}

/******************
Translate functions
******************/

void TransformComponent::Translate(float translateX, float translateY, float translateZ)
{
	m_vPosition += Vector3(translateX, translateY, translateZ);
}

void TransformComponent::Translate(Vector3 arg)
{
	m_vPosition += arg;
}
void TransformComponent::TranslateRelative(float translateX, float translateY, float translateZ)
{
	m_vRelativePosition += Vector3(translateX, translateY, translateZ);
}

void TransformComponent::TranslateRelative(Vector3 arg)
{
	m_vRelativePosition += arg;
}

/***************
Getter Functions
***************/

Vector3 TransformComponent::GetPosition()
{
	return m_vPosition;
}
Vector3 TransformComponent::GetRelativePosition()
{
	return m_vRelativePosition;
}
Vector3 TransformComponent::GetRotation()
{
	return m_vRotateAxis;
}
Vector3 TransformComponent::GetScale()
{
	return m_vScale;
}

float TransformComponent::GetDegrees()
{
	return m_fdegrees;
}