#include "EntityScript.h"
#include "PlayerScript.h"
#include "LootScript.h"
#include "RenderComponent.h"
#include "Utility.h"
#include "PlayerDeathScript.h"

EntityScript::EntityScript(Behaviour* Behaviour)
	: m_Behaviour(Behaviour),
	m_SW()
{
	if (m_Behaviour)
		m_Behaviour->Init(this);
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
}
EntityScript::EntityScript(Behaviour * Behaviour, const Stats & Stats)
	: m_Behaviour(Behaviour)
	, m_BaseStats(Stats)
{
	m_Values.SetHealth(Stats.GetMaxHealth());
	if (m_Behaviour)
		m_Behaviour->Init(this);
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
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
}
EntityScript::~EntityScript()
{
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
void EntityScript::SetCanJump(bool b)
{
	m_bCanJump = b;
}
bool EntityScript::GetCanJump()
{
	return m_bCanJump;
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
	if (m_Values.m_iHealth <= 0)
	{
		if (this->GetComponent<PlayerScript>(true))
		{
			this->GetComponent<PlayerDeathScript>()->SetActive(true);
			Notify("PlayerDied");
			RENDER->ResetColor();
			return true;
		}
		if (this->LOOT)
		{
			this->LOOT->DropLoot();
		}
		Notify("EntityDied");
		DestroySelf(); // should switch to play death anim
		return true;
	}
	return false;
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

	float newAngle = Lerp(TargetAngle, CurrentAngle, 0.9f);
	TRANS->SetRotation(newAngle, 0, 1, 0);
}
void EntityScript::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	if (m_bCanJump)
	{
		rb->SetVel(Vector3(rb->GetVel().x, 40 / rb->GetMass(), rb->GetVel().z));
		m_bCanJump = false;
		if (GetComponent<PlayerScript>() != nullptr)
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