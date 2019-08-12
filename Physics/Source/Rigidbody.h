#pragma once
#include "ComponentBase.h"
#include "PhysicsMaterial.h"
class Rigidbody :
	public ComponentBase
{
public:
	enum ePhysicsTypes
	{
		NONE,
		BALL,
		PILLAR,
		WALL,
		SQUARE,
		BOX,
		PADDLE,
		TOTAL,
	};
private:
	Vector3 m_vAVel;
	Vector3 m_vTorque;

	Vector3 m_vVel;
	Vector3 m_vForce;

	Vector3 m_vGravityExponent;
	// PhysicsMat m_PhysicsMat
	float m_fMass;

	bool m_bLockXAxis;
	bool m_bLockYAxis;
	bool m_bLockZAxis;

	bool m_bGravityAffected;
	ePhysicsTypes m_eType;
	PhysicsMaterial m_PhyMat;
public:
	Rigidbody(ePhysicsTypes e, bool Grav = true);
	virtual ~Rigidbody();
	virtual ComponentBase* Clone()
	{
		return new Rigidbody(*this);
	}
	virtual void Update(double dt) override;

	// Get
	Vector3 GetVel();
	Vector3 GetAVel();
	float GetMass();
	ePhysicsTypes GetType();
	PhysicsMaterial GetMat();
	// Grav
	void SetGravityX(float x);
	void SetGravity(Vector3 v);
	void LockXAxis(bool);
	void LockYAxis(bool);
	void LockZAxis(bool);
	// Set
	void SetMass(float f);
	void SetVel(Vector3);
	void SetAVel(Vector3);
	void SetTorque(Vector3);
	void AddForce(Vector3);
	void SetMat(float, float);

	void ClampVel(float max);
};
