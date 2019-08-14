#include "EntityScript.h"

#define DAMAGE_TIME 3.f
#define COLOR_TIME 0.5f

EntityScript::EntityScript()
{
	m_fMoveForce = 300;
	m_fMaxSpeed = 1;
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fHealth = 100;
	m_fAnimStartTime = -1;
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
	if (m_fHealth <= 0)
	{
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
	m_RB->AddForce(vDir * m_fMoveForce);
	m_RB->ClampVelXZ(m_fMaxSpeed);
}
void EntityScript::SetMovementSpeed(float Force, float Max)
{
	m_fMoveForce = Force;
	m_fMaxSpeed = Max;
}
void EntityScript::Damage(float fDamage)
{
	m_bDamageAnim = true;
	RENDER->SetColor(20, 20, 20);
	m_SW.Start();
	m_fHealth -= fDamage;
}