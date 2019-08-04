#include "ChengRigidbody.h"
#include "TransformComponent.h"
#include "WorldValues.h"
ChengRigidbody::ChengRigidbody(ePhysicsTypes e, bool Grav)
	: m_bLockXAxis{ false }
	, m_bLockYAxis{ false }
	, m_bLockZAxis{ false }
	, m_eType{ e }
{
	m_fMass = 1;
	m_vGravity = { 0,-1,0 };

	m_bGravityAffected = Grav;
	this->SetActive(true);
}

ChengRigidbody::~ChengRigidbody()
{
}
void ChengRigidbody::Update(double dt)
{
	//dt *= WorldValues::TimeScale;
	Vector3 vAccel = m_vForce * (1 / m_fMass);
	m_vForce.SetZero();
	Vector3 CurrentGrav = m_vGravity + WorldValues::DefaultGravity;
	CurrentGrav.x *= WorldValues::GravityExponent.x;
	CurrentGrav.y *= WorldValues::GravityExponent.y;
	CurrentGrav.z *= WorldValues::GravityExponent.z;
	if (m_bGravityAffected)
		vAccel += CurrentGrav;
	// Friction
	float coeff = m_PhyMat.GetFriction();

	this->m_vVel += vAccel * (float)dt * WorldValues::TimeScale;
	if (m_bLockXAxis)
		m_vVel.x = 0;
	if (m_bLockYAxis)
		m_vVel.y = 0;
	if (m_bLockZAxis)
		m_vVel.z = 0;
	TransformComponent* Trans = this->GetComponent<TransformComponent>();
	Trans->Translate(m_vVel * (float)dt * WorldValues::TimeScale);
	m_vVel = m_vVel * this->m_PhyMat.GetFriction();
	float I = this->m_fMass * (Trans->GetScale().x * Trans->GetScale().x);
	Vector3 vAAccel = this->m_vTorque * (1.f / I);
	m_vAVel += vAAccel * (float)dt;
	float deg = Trans->GetDegrees();
	deg += m_vAVel.y * (float)dt * WorldValues::TimeScale;
	if (m_vAVel.y != 0)
		Trans->SetRotation(deg, 0, 1, 0);
	//m_vAVel.SetZero();
	m_vTorque.SetZero();
}
void ChengRigidbody::SetTorque(Vector3 v)
{
	if (WorldValues::TimeScale > 0)
		this->m_vTorque = v;
	else
		this->m_vTorque = -v;
}
void ChengRigidbody::SetVel(Vector3 v)
{
	if (WorldValues::TimeScale > 0)
		this->m_vVel = v;
	else
		this->m_vVel = -v;
}
void ChengRigidbody::SetAVel(Vector3 v)
{
	if (WorldValues::TimeScale > 0)
		this->m_vAVel = v;
	else
		this->m_vAVel = -v;
}
void ChengRigidbody::IncrementForce(Vector3 v)
{
	if (WorldValues::TimeScale > 0)
		m_vForce += v;
	else
		m_vForce += -v;
}
Vector3 ChengRigidbody::GetVel()
{
	if (WorldValues::TimeScale > 0)
		return m_vVel;
	else
		return -m_vVel;
}
Vector3 ChengRigidbody::GetAVel()
{
	if (WorldValues::TimeScale > 0)
		return m_vAVel;
	else
		return -m_vAVel;
}
float ChengRigidbody::GetMass()
{
	return m_fMass;
}
void ChengRigidbody::SetMass(float f)
{
	m_fMass = f;
}
ChengRigidbody::ePhysicsTypes ChengRigidbody::GetType()
{
	return m_eType;
}
// Grav
void ChengRigidbody::SetGravityX(float x)
{
	if (WorldValues::TimeScale > 0)
		this->m_vGravity.x = x;
	else
		this->m_vGravity.x = -x;
}
void ChengRigidbody::LockXAxis(bool b)
{
	m_bLockXAxis = b;
}
void ChengRigidbody::LockYAxis(bool b)
{
	m_bLockYAxis = b;
}
void ChengRigidbody::LockZAxis(bool b)
{
	m_bLockZAxis = b;
}
void ChengRigidbody::SetMat(float f, float b)
{
	m_PhyMat.SetMat(f, b);
}
PhysicsMaterial ChengRigidbody::GetMat()
{
	return m_PhyMat;
}