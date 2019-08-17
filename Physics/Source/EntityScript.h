#pragma once
#include "ScriptComponent.h"
#include "Rigidbody.h"
#include "StopWatch.h"

#define DAMAGE_TIME 1.f
#define COLOR_TIME 0.5f

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
	bool m_bDamageAnim;
	float m_fAnimStartTime;
	//--------------------------------------------------------------------------------
	void Log();
	bool CheckRB();
	void Init();
	void CheckInit();
	void DamageAnim();
	StopWatch m_SW;
protected:
	Rigidbody* m_RB;
	//--------------------------------------------------------------------------------
	void Move(Vector3 vDir);
public:
	EntityScript();
	virtual ~EntityScript();
	virtual Component* Clone() { return new EntityScript(*this); };
	virtual void Update(double dt) override;

	void SetMovementSpeed(float Force, float Max);
	void SetForce(float force);
	float GetForce();
	void SetMaxSpeed(float maxspeed);
	float GetMaxSpeed();
	void SetHealth(float health);
	float GetHealth();
	StopWatch GetSW();
	bool IsDamageAnim();
	void SetDamageAnim(bool);
	void Damage(float fDamage);
};
