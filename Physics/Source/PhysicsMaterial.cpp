#include "PhysicsMaterial.h"

PhysicsMaterial::PhysicsMaterial()
{
	m_fFriction = 1;
	m_fBounciness = 1;
}
PhysicsMaterial::PhysicsMaterial(float fric, float bounce)
{
	m_fFriction = fric;
	m_fBounciness = bounce;
}
PhysicsMaterial::~PhysicsMaterial()
{
}
void  PhysicsMaterial::SetMat(float fric, float bounce)
{
	m_fFriction = fric;
	m_fBounciness = bounce;
}
float  PhysicsMaterial::GetFriction()
{
	return m_fFriction;
}
float PhysicsMaterial::GetBounce()
{
	return m_fBounciness;
}