#include "AbilityGrenade.h"
#include "PlayerScript.h"

AbilityGrenade::AbilityGrenade()
	: AbilityBase(0.f, 10.f, 75.f)
{
}

AbilityGrenade::AbilityGrenade(const float cooldowntime, const float cost)
	: AbilityBase(0.f, cooldowntime, cost)
{
}

AbilityGrenade::~AbilityGrenade()
{
}

void AbilityGrenade::Use(Component* com)
{
	com->GetComponent<PlayerScript>()->PullPin();
	com->GetComponent<PlayerScript>()->GetValues()->OffsetStamina(m_fStaminaCost);
	m_bInUse = true;
	m_SW.Start();
}

void AbilityGrenade::StopUse(Component* com)
{
	com->GetComponent<PlayerScript>()->ThrowGrenade();
}
