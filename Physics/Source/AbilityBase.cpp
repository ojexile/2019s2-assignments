#include "AbilityBase.h"

AbilityBase::AbilityBase(const float usetime, const float cooldowntime, const float cost)
	: m_fUseTime(usetime),
	m_fCooldownTime(cooldowntime),
	m_fStaminaCost(cost),
	m_bInUse(false),
	//m_bCanUse(true),
	m_SW()
{

}

AbilityBase::~AbilityBase()
{
}

void AbilityBase::Update(Component* com)
{
	

	if (m_SW.GetTime() > m_fUseTime)
	{
		StopUse(com);
	}

	if (m_SW.GetTime() > m_fCooldownTime + m_fUseTime)
	{
		//	m_bCanUse = true;
		m_bInUse = false;
		m_SW.Reset();
	}
}

float AbilityBase::GetPercentageCooldownDone()
{
	float returnval = (m_SW.GetTime() / m_fCooldownTime);
	Math::Clamp(returnval, 0.f, 100.f);

	return returnval;
}

bool AbilityBase::IsInUse()
{
	return m_bInUse;
}