#pragma once
#include "ComponentBase.h"
class ChengRigidbody :
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
	Vector3 m_vVel;
	Vector3 m_vAVel;
	Vector3 m_vForce;
	Vector3 m_vGravity;
	// PhysicsMat m_PhysicsMat
	float m_fMass;

	bool m_bLockXAxis;
	bool m_bLockYAxis;
	bool m_bLockZAxis;

	bool m_bGravityAffected;
	ePhysicsTypes m_eType;
public:
	ChengRigidbody(ePhysicsTypes e, bool Grav = true);
	virtual ~ChengRigidbody();
	virtual ComponentBase* Clone()
	{
		return new ChengRigidbody(*this);
	}
	virtual void Update(double dt) override;

	void SetVel(Vector3);
	void SetAVel(Vector3);
	Vector3 GetVel();
	Vector3 GetAVel();
	void IncrementForce(Vector3);
	float GetMass();
	void SetMass(float f);
	ePhysicsTypes GetType();
	// Grav
	void SetGravityX(float x);
	void LockXAxis(bool);
	void LockYAxis(bool);
	void LockZAxis(bool);
};
