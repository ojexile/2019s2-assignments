#include "AbilityDash.h"
#include "PlayerScript.h"

AbilityDash::AbilityDash(const float cooldowntime, const float cost)
	: AbilityBase(0.f, cooldowntime, cost)
{

}

void AbilityDash::Use(Component* com)
{
	com->GetComponent<PlayerScript>()->Dash();
	m_SW.Start();
}

void AbilityDash::StopUse(Component* com)
{

}

void AbilityDash::Update(double dt)
{
}
