#include "Stats.h"

Stats::Stats()
{
	m_iHealthMax = 100;
	m_fStaminaRegenRate = 20;
	m_fStaminaMax = 100;
	m_fMaxMovementSpeed = 30;
	m_fMovementForce = 40;
}

Stats::~Stats()
{
}

void Stats::SetZero()
{
	m_iHealthMax = 0;
	m_fStaminaRegenRate = 0;
	m_fStaminaMax = 0;
	m_fMaxMovementSpeed = 0;
	m_fMovementForce = 0;
}
void Stats::SetOne()
{
	m_iHealthMax = 1;
	m_fStaminaRegenRate = 1;
	m_fStaminaMax = 1;
	m_fMaxMovementSpeed = 1;
	m_fMovementForce = 1;
}

void Stats::SetMaxHealth(int i)
{
	m_iHealthMax = i;
}

void Stats::SetMaxStamina(float f)
{
	m_fStaminaMax = f;
}

int Stats::GetMaxHealth() const
{
	return m_iHealthMax;
}

float Stats::GetMaxStamina() const
{
	return m_fStaminaMax;
}

void Stats::SetStaminaRegen(float f)
{
	m_fStaminaRegenRate = f;
}

void Stats::SetMovement(float max, float force)
{
	m_fMaxMovementSpeed = max;
	m_fMovementForce = force;
}

void Stats::AffectStaminaRegenRate(float f)
{
	m_fStaminaRegenRate *= f;
}

void Stats::AffectMaxStamina(float f)
{
	m_fStaminaMax *= f;
}