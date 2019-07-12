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
		WALL,
		SQUARE,
		BOX,
		PILLAR,
		TOTAL,
	};
private:
	Vector3 m_vVel;
	Vector3 m_vNormal;
	ePhysicsTypes m_eType;
	float m_fMass;
public:
	ChengRigidbody(ePhysicsTypes e);
	virtual ~ChengRigidbody();
	virtual ComponentBase* Clone()
	{
		return new ChengRigidbody(*this);
	}
	virtual void Update(double dt) override;

	void SetVel(Vector3);
	void SetNormal(Vector3);

	//--------------------------------------------------------------------------------
	friend class ChengCollisionManager;
};
