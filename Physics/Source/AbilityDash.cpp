#include "AbilityDash.h"
#include "PlayerScript.h"

AbilityDash::AbilityDash(const float cooldowntime, const float cost)
	: AbilityBase(0.f, cooldowntime, cost)
{
	
}

AbilityDash::~AbilityDash()
{
}

void AbilityDash::Use(Component* com)
{
	com->GetComponent<PlayerScript>()->Dash();
	com->GetComponent<PlayerScript>()->GetValues()->OffsetStamina(-m_fStaminaCost);
	m_bInUse = true;
	m_bCanUse = false;
	m_SW.Start();
}

void AbilityDash::StopUse(Component* com)
{
}

