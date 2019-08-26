#include "AbilityBase.h"

AbilityBase::AbilityBase(const float usetime, const float cooldowntime, const float cost)
	: m_fUseTime(usetime),
	m_fCooldownTime(cooldowntime),
	m_fStaminaCost(cost),
	m_bInUse(false),
	m_bCanUse(true),
	m_SW()
{

}

AbilityBase::~AbilityBase()
{
}
