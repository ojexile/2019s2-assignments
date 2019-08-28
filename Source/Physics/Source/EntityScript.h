#pragma once
#include "ScriptComponent.h"
#include "Rigidbody.h"
#include "StopWatch.h"
#include "Stats.h"
#include "EntityValues.h"
#include "Behaviour.h"

#define DAMAGE_TIME .4f

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
	void UpdateValues();
	bool m_bCanDie;
protected:
	bool m_bIsDead;
	EntityValues m_Values;
	Behaviour* m_Behaviour;
	const Stats m_BaseStats;
	Stats m_AdditionalStats;
	StopWatch m_SW;
	Rigidbody* m_RB;
	bool m_bInitialised;
	bool m_bDamageAnim;
	float m_fAnimStartTime;
	bool m_bCanJump;
	bool m_bIsBoss;
	//--------------------------------------------------------------------------------
	bool CheckDeath();
public:
	EntityScript(Behaviour* Behaviour = nullptr);
	EntityScript(Behaviour* Behaviour, const Stats &Stats);
	EntityScript(EntityScript& ref);
	virtual ~EntityScript();
	virtual Component* Clone() { return new EntityScript(*this); };
	virtual void Update(double dt) override;
	virtual void Start() override;

	const Stats* GetBaseStats();
	Stats* GetAdditionalStats();
	EntityValues* GetValues();

	void Move(Vector3 vDir);
	void MoveForwards();
	void RotateTowards(Vector3 vDir);
	void Jump();
	bool IsDamageAnim();
	void SetDamageAnim(bool);
	virtual void Damage(int iDamage);
	void UpdateBehaviour();
	void SetCanJump(bool b);
	bool GetCanJump();
	Behaviour* GetBehaviour();
	void SetCanDie(bool);
	bool GetCanDie();
	void SetBoss();
};
