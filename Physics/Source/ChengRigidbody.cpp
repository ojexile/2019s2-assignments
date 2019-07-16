#include "ChengRigidbody.h"
#include "TransformComponent.h"
ChengRigidbody::ChengRigidbody(ePhysicsTypes e, bool Grav)
{
	m_eType = e;
	m_fMass = 1;
	m_vGravity = { 0,-40.8f,0 };
	m_bLockXAxis = false;
	m_bLockYAxis = false;
	m_bLockZAxis = false;
	m_bGravityAffected = Grav;
}

ChengRigidbody::~ChengRigidbody()
{
}
void ChengRigidbody::Update(double dt)
{
	Vector3 m_vAccel = m_vForce * (1 / m_fMass);
	if(m_bGravityAffected)
		m_vAccel += m_vGravity;
	this->m_vVel += m_vAccel * (float)dt;
	TransformComponent* Trans = this->GetComponent<TransformComponent>();
	Trans->Translate(m_vVel * (float)dt);
}
void ChengRigidbody::SetVel(Vector3 v)
{
	this->m_vVel = v;
}
Vector3 ChengRigidbody::GetVel()
{
	return m_vVel;
}
float ChengRigidbody::GetMass()
{
	return m_fMass;
}
ChengRigidbody::ePhysicsTypes ChengRigidbody::GetType()
{
	return m_eType;
}