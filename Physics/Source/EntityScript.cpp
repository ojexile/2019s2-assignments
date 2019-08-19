#include "EntityScript.h"
#include "PlayerScript.h"
#include "LootScript.h"
#include "RenderComponent.h"

EntityScript::EntityScript(Behaviour* Behaviour)
	:m_Behaviour(Behaviour)
{
	if (m_Behaviour)
		m_Behaviour->Init(this);
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
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
	if(m_Behaviour)
		m_Behaviour->Update();
	// Check death
	if (CheckDeath())
		return;
	if (m_SW.Stop()->GetTime() >= DAMAGE_TIME)
	{
		m_bDamageAnim = false;
		RENDER->ResetColor();
	}
	UpdateValues();
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
	if (m_Values.m_iHealth <= 0 && !this->GetComponent<PlayerScript>())
	{
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
void EntityScript::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->AddForce({ 0,m_BaseStats.m_fJumpForce,0 });
	rb->SetVel(Vector3(rb->GetVel().x, 0, rb->GetVel().z));
	Notify("Jump");
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