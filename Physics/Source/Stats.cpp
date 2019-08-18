#include "Stats.h"

Stats::Stats()
{
	m_iHealthMax = 100;
	m_fStaminaRegenRate = 40;
	m_fStaminaMax = 100;
	m_fMaxMovementSpeed = 40;
	m_fMovementForce = 300;
}

Stats::~Stats()
{
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