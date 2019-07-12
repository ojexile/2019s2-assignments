#include "ChengRigidbody.h"
#include "TransformComponent.h"
ChengRigidbody::ChengRigidbody(ePhysicsTypes e)
{
	m_eType = e;
	m_fMass = 1;
	m_vGravity = { 0,-40.8f,0 };
}

ChengRigidbody::~ChengRigidbody()
{
}
void ChengRigidbody::Update(double dt)
{
	Vector3 m_vAccel = m_vForce * (1 / m_fMass);
	m_vAccel += m_vGravity;
	if (m_eType == BALL)
		this->m_vVel += m_vAccel * (float)dt;
	TransformComponent* Trans = this->GetComponent<TransformComponent>();
	Trans->Translate(m_vVel * (float)dt);
}
void ChengRigidbody::SetVel(Vector3 v)
{
	this->m_vVel = v;
}
void ChengRigidbody::SetNormal(Vector3 v)
{
	this->m_vNormal = v;
}