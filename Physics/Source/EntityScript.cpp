#include "EntityScript.h"
#include "PlayerScript.h"
#include "LootScript.h"
#include "RenderComponent.h"
#include "Utility.h"
#include "WinLoseScript.h"
#include "Behaviour.h"

EntityScript::EntityScript(Behaviour* _Behaviour)
{
	if (_Behaviour)
	{
		m_Behaviour = new Behaviour(*_Behaviour);
		m_Behaviour->Init(this);
	}
	else
		m_Behaviour = nullptr;
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
	m_bIsDead = false;
	m_bCanDie = true;
}
EntityScript::EntityScript(Behaviour * _Behaviour, const Stats & Stats)
	: m_BaseStats(Stats)
{
	m_Values.SetHealth(Stats.GetMaxHealth());
	if (_Behaviour)
	{
		m_Behaviour = new Behaviour(*_Behaviour);
		m_Behaviour->Init(this);
	}
	else
		m_Behaviour = nullptr;
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
	m_bIsDead = false;
	m_bCanDie = true;
}
EntityScript::EntityScript(EntityScript & ref)
	: m_BaseStats(ref.m_BaseStats)
{
	m_Values = ref.m_Values;
	m_AdditionalStats = ref.m_AdditionalStats;

	if (ref.m_Behaviour)
	{
		m_Behaviour = new Behaviour(*ref.m_Behaviour);
		m_Behaviour->Init(this);
	}
	else
		m_Behaviour = nullptr;
	m_bInitialised = false;
	m_fAnimStartTime = 0;
	m_bIsDead = false;
	m_bCanDie = ref.m_bCanDie;
}
EntityScript::~EntityScript()
{
	delete m_Behaviour;
}
void EntityScript::Init()
{
	m_RB = RIGID;
}
void EntityScript::CheckInit()
{
	if (!m_bInitialised)
	{
		Init();
	}
}
void EntityScript::Update(double dt)
{
	// Check death
	if (CheckDeath())
		return;
	if (m_SW.Stop()->GetTime() >= DAMAGE_TIME && m_bDamageAnim)
	{
		m_bDamageAnim = false;
		RENDER->ResetColor();
	}
	UpdateValues();
}
void EntityScript::Start()
{
	m_Values.m_iHealth = m_BaseStats.m_iHealthMax;
	m_Values.m_fStamina = m_BaseStats.m_fStaminaMax;
}
void EntityScript::SetCanJump(bool b)
{
	m_bCanJump = b;
}
bool EntityScript::GetCanJump()
{
	return m_bCanJump;
}
Behaviour * EntityScript::GetBehaviour()
{
	return m_Behaviour;
}
void EntityScript::SetCanDie(bool b)
{
	m_bCanDie = b;
}
bool EntityScript::GetCanDie()
{
	return m_bCanDie;
}
const Stats * EntityScript::GetBaseStats()
{
	return &m_BaseStats;
}
Stats * EntityScript::GetAdditionalStats()
{
	return &m_AdditionalStats;
}
EntityValues * EntityScript::GetValues()
{
	return &m_Values;
}
void EntityScript::DamageAnim()
{
}
bool EntityScript::CheckDeath()
{
	if (!m_bCanDie)
		return false;

	if (m_Values.m_iHealth <= 0 && !m_bIsDead)
	{
		if (this->GetComponent<PlayerScript>(true))
		{
			this->GetComponent<WinLoseScript>()->SetActive(true);
			this->GetComponent<PlayerScript>(true)->StartDeathAnim();
			Notify("PlayerDied");
			RENDER->ResetColor();
			m_bIsDead = true;
			return m_bIsDead;
		}
		else if (this->GetComponent<LootScript>(true))
		{
			this->LOOT->DropLoot();
		}
		Notify("EntityDied");
		DestroySelf(); // should switch to play death anim
		m_bIsDead = true;
	}
	return m_bIsDead;
}
void EntityScript::UpdateValues()
{
	// Update Values
	m_Values.m_fStamina += m_BaseStats.m_fStaminaRegenRate * m_AdditionalStats.m_fStaminaRegenRate * Time::GetInstance()->GetDeltaTimeF();
	m_Values.m_fStamina = Math::Clamp(m_Values.m_fStamina, 0.f, m_BaseStats.m_fStaminaMax * m_AdditionalStats.m_fStaminaMax);
}
void EntityScript::Log()
{
	DEFAULT_LOG("No rigidbody attached to entity.");
}
bool EntityScript::CheckRB()
{
	if (!m_RB)
	{
		Log();
		return false;
	}
	return true;
}
void EntityScript::Move(Vector3 vDir)
{
	CheckInit();
	if (!CheckRB())
		return;
	m_RB->AddForce(vDir * m_BaseStats.m_fMovementForce + vDir * m_AdditionalStats.m_fMovementForce);
	m_RB->ClampVelXZ(m_BaseStats.m_fMaxMovementSpeed + m_AdditionalStats.m_fMaxMovementSpeed);
}
void EntityScript::MoveForwards()
{
	float CurrentAngle = TRANS->GetDegrees();

	float CurrentRad = Math::DegreeToRadian(CurrentAngle);
	Vector3 Front = { sin(CurrentRad), 0, cos(CurrentRad) };
	Move(Front);
}
void EntityScript::RotateTowards(Vector3 vDir)
{
	if (vDir.IsZero())
		return;
	vDir.y = 0;
	float TargetAngle = AngleBetween({ 1,0,1 }, vDir);
	if (vDir.Cross({ 1,0,1 }).y > 0)
		TargetAngle = -TargetAngle;
	// current angle
	float CurrentAngle = TRANS->GetDegrees();

	float newAngle = LerpAngle(TargetAngle, CurrentAngle, 0.01f);
	TRANS->SetRotation(newAngle, 0, 1, 0);
}
void EntityScript::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	if (m_bCanJump)
	{
		rb->SetVel(Vector3(rb->GetVel().x, 40 / rb->GetMass(), rb->GetVel().z));
		m_bCanJump = false;
		if (GetComponent<PlayerScript>(true) != nullptr)
		{
			Notify("Jump");
		}
	}
}
bool EntityScript::IsDamageAnim()
{
	return m_bDamageAnim;
}

void EntityScript::SetDamageAnim(bool anim)
{
	m_bDamageAnim = anim;
}
void EntityScript::Damage(int iDamage)
{
	if (m_bDamageAnim)
		return;
	m_bDamageAnim = true;
	RENDER->SetColor(50, 50, 50);
	m_SW.Start();
	m_Values.m_iHealth -= iDamage;
}

void EntityScript::UpdateBehaviour()
{
	if (m_Behaviour)
		m_Behaviour->Update();
}