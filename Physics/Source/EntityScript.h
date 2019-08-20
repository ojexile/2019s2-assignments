#pragma once
#include "ScriptComponent.h"
#include "Rigidbody.h"
#include "StopWatch.h"
#include "Stats.h"
#include "EntityValues.h"
#include "Behaviour.h"

#define DAMAGE_TIME 1.f

/********************************************************************************/
/*!
\author Hao Cheng
\brief
Script to handle entity movement. Input / AI scripts should communicate through this to move
entity
/*!
/********************************************************************************/
class EntityScript : public ScriptComponent
{
private:
	//--------------------------------------------------------------------------------
	void Log();
	bool CheckRB();
	void Init();
	void CheckInit();
	void DamageAnim();
	bool CheckDeath();
	void UpdateValues();
protected:
	EntityValues m_Values;
	Behaviour* m_Behaviour;
	const Stats m_BaseStats;
	Stats m_AdditionalStats;
	StopWatch m_SW;
	Rigidbody* m_RB;
	bool m_bInitialised;
	bool m_bDamageAnim;
	float m_fAnimStartTime;
	//--------------------------------------------------------------------------------
public:
	EntityScript(Behaviour* Behaviour = nullptr);
	EntityScript(Behaviour* Behaviour, const Stats &Stats);
	EntityScript(EntityScript& ref);
	virtual ~EntityScript();
	virtual Component* Clone() { return new EntityScript(*this); };
	virtual void Update(double dt) override;

	const Stats* GetBaseStats();
	Stats* GetAdditionalStats();
	EntityValues* GetValues();

	void Move(Vector3 vDir);
	void MoveForwards();
	void RotateTowards(Vector3 vDir);
	void Jump();
	bool IsDamageAnim();
	void SetDamageAnim(bool);
	void Damage(int iDamage);
};
