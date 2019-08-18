#include "Stats.h"

Stats::Stats()
{
	m_iHealthMax = 100;
	m_fStaminaRegenRate = 40;
	m_fStaminaMax = 100;
	m_fMaxMovementSpeed = 1;
	m_fMovementForce = 100;
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

void Stats::SetHealth(int i)
{
	m_iHealthMax = i;
}

void Stats::SetStamina(float f)
{
	m_fStaminaMax = f;
}

int Stats::GetHealth()
{
	return m_iHealthMax;
}

float Stats::GetStamina()
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