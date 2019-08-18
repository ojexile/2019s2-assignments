#include "EntityScript.h"
#include "PlayerScript.h"
#include "LootScript.h"
#include "RenderComponent.h"

EntityScript::EntityScript()
{
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
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
	if (m_Values.m_iHealth <= 0 && !this->GetComponent<PlayerScript>())
	{
		if (this->LOOT)
		{
			this->LOOT->DropLoot();
		}
		Notify("EntityDied");
		DestroySelf(); // should switch to play death anim
		return;
	}
	if (m_SW.Stop()->GetTime() >= DAMAGE_TIME)
	{
		m_bDamageAnim = false;
		RENDER->ResetColor();
	}
	if (m_bDamageAnim)
	{
	}
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