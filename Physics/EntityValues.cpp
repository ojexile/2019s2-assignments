#include "Source\EntityValues.h"

EntityValues::EntityValues()
{
	m_iHealth = 100;
	m_fStamina = 100;
}

EntityValues::~EntityValues()
{
}

float EntityValues::GetStamina()
{
	return m_fStamina;
}

int EntityValues::GetHealth()
{
	return m_iHealth;
}

void EntityValues::SetHealth(int i)
{
	m_iHealth = i;
}