#include "Rigidbody.h"
#include "TransformComponent.h"
#include "WorldValues.h"
Rigidbody::Rigidbody(ePhysicsTypes e, bool Grav)
	: m_bLockXAxis{ false }
	, m_bLockYAxis{ false }
	, m_bLockZAxis{ false }
	, m_eType{ e }
{
	m_fMass = 1;
	m_vGravityExponent = { 1,1,1 };

	m_bGravityAffected = Grav;
	this->SetActive(true);
	m_bResponseActive = true;
}

Rigidbody::~Rigidbody()
{
}
void Rigidbody::Update(double dt)
{
	if (this->m_eType == ePhysicsTypes::NONE) return;
	dt *= WorldValues::TimeScale;
	if(m_iMapForceCount != 0) m_vForce += m_vMapForce * (1.f / m_iMapForceCount);
	m_vMapForce.SetZero();
	m_iMapForceCount = 0;
	Vector3 vAccel = m_vForce * (1 / m_fMass);
	m_vForce.SetZero();
	Vector3 CurrentGrav = WorldValues::DefaultGravity;
	CurrentGrav.x *= WorldValues::GravityExponent.x;
	CurrentGrav.y *= WorldValues::GravityExponent.y;
	CurrentGrav.z *= WorldValues::GravityExponent.z;

	CurrentGrav.x *= m_vGravityExponent.x;
	CurrentGrav.y *= m_vGravityExponent.y;
	CurrentGrav.z *= m_vGravityExponent.z;
	if (m_bGravityAffected)
		vAccel += CurrentGrav;
	// Friction
	float coeff = m_PhyMat.GetFriction();

	this->m_vVel += vAccel * (float)dt;
	if(m_iVelChangeCount != 0) this->m_vVel += m_vVelChange * (1.f / m_iVelChangeCount);
	m_vVelChange.SetZero();
	m_iVelChangeCount = 0;
	// Air Resistance
	float fric = m_PhyMat.GetFriction();
	Vector3 vScale = TRANS->GetScale();
	// Set volume as cuboid
	float volume = vScale.x * vScale.y * vScale.z;
	float density = m_fMass / volume;
	float area = volume; // ignore cross section area, use raw volume
	Vector3 fDrag = 0.5f * density * m_vVel * area * fric * WorldValues::DragCoeff * (float)dt;
	m_vVel -= fDrag;
	if (m_bLockXAxis)
		m_vVel.x = 0;
	if (m_bLockYAxis)
		m_vVel.y = 0;
	if (m_bLockZAxis)
		m_vVel.z = 0;
	TransformComponent* Trans = this->GetComponent<TransformComponent>();
	Trans->Translate(m_vVel * (float)dt );
	// Angular
	// note: angular only affects y axis
	float I = this->m_fMass * (Trans->GetScale().x * Trans->GetScale().x);
	Vector3 vAAccel = this->m_vTorque * (1.f / I);
	m_vAVel += vAAccel * (float)dt;
	float deg = Trans->GetDegrees();
	deg += m_vAVel.y * (float)dt ;
	if (m_vAVel.y != 0)
		Trans->SetRotation(deg, 0, 1, 0);
	m_vTorque.SetZero();
}
void Rigidbody::SetTorque(Vector3 v)
{
		this->m_vTorque = v;
}
void Rigidbody::SetVel(Vector3 v)
{
		this->m_vVel = v;
}
void Rigidbody::SetAVel(Vector3 v)
{
		this->m_vAVel = v;
}
void Rigidbody::AddForce(Vector3 v)
{
		m_vForce += v;
}
Vector3 Rigidbody::GetVel()
{
		return m_vVel;
}
void Rigidbody::QueueVel(Vector3 v)
{
	m_vVelChange += v;
	m_iVelChangeCount += 1;
}
Vector3 Rigidbody::GetAVel()
{
		return m_vAVel;
}
float Rigidbody::GetMass()
{
	return m_fMass;
}
void Rigidbody::SetMass(float f)
{
	m_fMass = f;
}
Rigidbody::ePhysicsTypes Rigidbody::GetType()
{
	return m_eType;
}
// Grav
void Rigidbody::SetGravityX(float x)
{
		this->m_vGravityExponent.x = x;
}
void Rigidbody::SetGravity(Vector3 v)
{
	this->m_vGravityExponent = v;
}
void Rigidbody::LockXAxis(bool b)
{
	m_bLockXAxis = b;
}
void Rigidbody::LockYAxis(bool b)
{
	m_bLockYAxis = b;
}
void Rigidbody::LockZAxis(bool b)
{
	m_bLockZAxis = b;
}
void Rigidbody::SetMat(float f, float b)
{
	m_PhyMat.SetMat(f, b);
}
PhysicsMaterial Rigidbody::GetMat()
{
	return m_PhyMat;
}
void Rigidbody::ClampVel(float max)
{
	if (m_vVel.LengthSquared() > max * max)
	{
		m_vVel = m_vVel.Normalized() * max;
	}
}
void Rigidbody::ClampVelXZ(float max)
{
	Vector3 vTemp = m_vVel;
	vTemp.y = 0;
	if (vTemp.LengthSquared() > max * max)
	{
		vTemp = m_vVel.Normalized() * max;
	}
	m_vVel.x = vTemp.x;
	m_vVel.z = vTemp.z;
}

void Rigidbody::QueueMapForce(Vector3 in)
{
	m_vMapForce += in;
	m_iMapForceCount++;
}


void Rigidbody::SetAffectedByGravity(bool AffectedByGrav)
{
	m_bGravityAffected = AffectedByGrav;
}

void Rigidbody::SetResponseActive(bool b)
{
	m_bResponseActive = b;
}
bool Rigidbody::GetResponseActive()
{
	return m_bResponseActive;
}