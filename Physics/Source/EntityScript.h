#pragma once
#include "ScriptComponent.h"
#include "Rigidbody.h"

/********************************************************************************/
/*!
\author Hao Cheng
\brief
Script to handle entity movement. Input / AI scripts should communicate through this to move 
entity
/*!
/********************************************************************************/
class EntityScript :
	public ScriptComponent
{
private:
	float m_fMoveForce;
	float m_fMaxSpeed;
	bool m_bInitialised;
	float m_fHealth;
	//--------------------------------------------------------------------------------
	void Log();
	bool CheckRB();
	void Init();
	void CheckInit();
protected:
	Rigidbody* m_RB;
	//--------------------------------------------------------------------------------
	void Move(Vector3 vDir);
public:
	EntityScript();
	virtual ~EntityScript();
	virtual ComponentBase* Clone() { return new EntityScript(*this); };

	void SetMovementSpeed(float Force, float Max);
};

