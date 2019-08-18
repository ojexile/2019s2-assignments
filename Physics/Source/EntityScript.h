#pragma once
#include "ScriptComponent.h"
#include "Rigidbody.h"
#include "StopWatch.h"
#include "Stats.h"

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
	Stats m_Stats;

	bool m_bInitialised;
	bool m_bDamageAnim;
	float m_fAnimStartTime;
	//--------------------------------------------------------------------------------
	void Log();
	bool CheckRB();
	void Init();
	void CheckInit();
	void DamageAnim();
protected:
	StopWatch m_SW;
	Rigidbody* m_RB;
	//--------------------------------------------------------------------------------
	void Move(Vector3 vDir);
public:
	EntityScript();
	virtual ~EntityScript();
	virtual Component* Clone() { return new EntityScript(*this); };
	virtual void Update(double dt) override;

	Stats* GetStats();

	bool IsDamageAnim();
	void SetDamageAnim(bool);
	void Damage(float fDamage);
};
