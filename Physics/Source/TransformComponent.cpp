#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	m_vPosition.SetZero();
	m_vRelativePosition.SetZero();
	m_vRotateAxis.SetZero();
	m_vRelativeRotateAxis.SetZero();
	m_vScale.Set(1, 1, 1);
	m_vRelativeScale.Set(1, 1, 1);
	m_fDegrees = 0.f;
	m_fRelativeDegrees = 0.f;
}

TransformComponent::TransformComponent(Vector3 pos)
{
	m_vPosition.Set(pos.x, pos.y, pos.z);
	m_vRelativePosition.SetZero();
	m_vRotateAxis.SetZero();
	m_vRelativeRotateAxis.SetZero();
	m_vScale.Set(1, 1, 1);
	m_vRelativeScale.Set(1, 1, 1);
	m_fDegrees = 0.f;
	m_fRelativeDegrees = 0.f;
}

TransformComponent::~TransformComponent()
{

}

/*****
Update
******/

void TransformComponent::Update(double dt)
{
	if (m_iQueuedTranslationCount != 0)
	m_vPosition += m_vQueuedTranslation * (1.f / m_iQueuedTranslationCount);
	m_vQueuedTranslation.SetZero();
	m_iQueuedTranslationCount = 0;
}

/***************
Setter functions
***************/

void TransformComponent::SetScale(float scaleX, float scaleY, float scaleZ)
{
	this->m_vScale.Set(scaleX, scaleY, scaleZ);
}
void TransformComponent::SetScale(Vector3 v)
{
	this->m_vScale.Set(v.x, v.y, v.z);
}
void TransformComponent::SetRelativeScale(Vector3 v)
{
	this->m_vRelativeScale.Set(v.x, v.y, v.z);
}
void TransformComponent::SetScale(float f)
{
	this->m_vScale.Set(f, f, f);
}
void TransformComponent::SetRelativeScale(float f)
{
	this->m_vRelativeScale.Set(f, f, f);
}

void TransformComponent::ScaleBy(Vector3 v)
{
	this->m_vScale += v;
}

void TransformComponent::SetRotation(float degrees, int xAxis, int yAxis, int zAxis)
{
	this->m_vRotateAxis.Set((float)xAxis, (float)yAxis, (float)zAxis);
	this->m_fDegrees = degrees;
}
void TransformComponent::SetRotation(float degrees, float xAxis, float yAxis, float zAxis)
{
	this->m_vRotateAxis.Set((float)xAxis, (float)yAxis, (float)zAxis);
	this->m_fDegrees = degrees;
}
void TransformComponent::SetRotation(float degrees, Vector3 v)
{
	this->m_vRotateAxis.Set(v.x, v.y, v.z);
	this->m_fDegrees = degrees;
}
void TransformComponent::SetRelativeRotation(float degrees, int xAxis, int yAxis, int zAxis)
{
	this->m_vRelativeRotateAxis.Set((float)xAxis, (float)yAxis, (float)zAxis);
	this->m_fRelativeDegrees = degrees;
}
void TransformComponent::SetRelativeRotation(float degrees, float xAxis, float yAxis, float zAxis)
{
	this->m_vRelativeRotateAxis.Set((float)xAxis, (float)yAxis, (float)zAxis);
	this->m_fRelativeDegrees = degrees;
}
void TransformComponent::SetRelativeRotation(float degrees, Vector3 v)
{
	this->m_vRelativeRotateAxis.Set(v.x, v.y, v.z);
	this->m_fRelativeDegrees = degrees;
}
void TransformComponent::RotateBy(float degrees, Vector3 v)
{
	this->m_vRotateAxis = { v.x, v.y, v.z };
	this->m_fDegrees += degrees;
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
void TransformComponent::QueueTranslate(Vector3 arg)
{
	m_vQueuedTranslation += arg;
	m_iQueuedTranslationCount++;
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
Vector3 TransformComponent::GetRelativeRotation()
{
	return m_vRelativeRotateAxis;
}
Vector3 TransformComponent::GetScale()
{
	return m_vScale;
}
Vector3 TransformComponent::GetRelativeScale()
{
	return m_vRelativeScale;
}
float TransformComponent::GetDegrees()
{
	return m_fDegrees;
}
float TransformComponent::GetRelativeDegrees()
{
	return m_fRelativeDegrees;
}