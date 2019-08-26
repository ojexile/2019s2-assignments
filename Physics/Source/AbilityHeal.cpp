#include "AbilityHeal.h"
#include "PlayerScript.h"
AbilityHeal::AbilityHeal(const float usetime, const float cooldown, const float cost, float totalhealedamount)
	: AbilityBase(usetime, cooldown, cost),
	m_fHealRate(totalhealedamount / usetime),
	m_bIsHealing(false)
{
}

AbilityHeal::~AbilityHeal()
{
}

void AbilityHeal::Use(Component* com)
{
	com->GetComponent<PlayerScript>()->GetValues()->OffsetStamina(m_fStaminaCost);
	m_bInUse = true;
	m_bIsHealing = true;
	m_SW.Start();
	m_fprevtime = m_SW.GetTime();
}

void AbilityHeal::StopUse(Component* com)
{
	m_bIsHealing = false;
}

void AbilityHeal::Update(Component* com)
{
	if (m_bIsHealing)
	{
		float newtime = m_SW.GetTime();
		while (newtime > m_fprevtime)
		{
			com->GetComponent<PlayerScript>()->GetValues()->HealHealth((int)(m_fHealRate));

			m_fprevtime += 1.f;
		}
	}

	AbilityBase::Update(com);
}
