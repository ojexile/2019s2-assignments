#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	m_vPosition.SetZero();
	m_vRotateAxis.SetZero();
	m_vScale.Set(1, 1, 1);
	m_fdegrees = 0.f;
}

TransformComponent::TransformComponent(Vector3 pos)
{
	m_vPosition.Set(pos.x, pos.y, pos.z);
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

void TransformComponent::setScale(float scaleX, float scaleY, float scaleZ)
{
	this->m_vScale.Set(scaleX, scaleY, scaleZ);
}

void TransformComponent::setRotation(float degrees, int xAxis, int yAxis, int zAxis)
{
	this->m_vRotateAxis.Set(xAxis, yAxis, zAxis);
	this->m_fdegrees = degrees;
}

void TransformComponent::setPosition(float translateX, float translateY, float translateZ)
{
	m_vPosition.Set(translateX, translateY, translateZ);
}

void TransformComponent::setPosition(Vector3 arg)
{
	this->m_vPosition = arg;
}

/******************
Translate functions
******************/

void TransformComponent::translateObject(float translateX, float translateY, float translateZ)
{
	m_vPosition += Vector3(translateX, translateY, translateZ);
}

void TransformComponent::translateObject(Vector3 arg)
{
	m_vPosition += arg;
}

/***************
Getter Functions
***************/

Vector3 TransformComponent::GetPosition()
{
	return m_vPosition;
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