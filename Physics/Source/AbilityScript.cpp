#include "AbilityScript.h"
#include "AbilityDash.h"
#include "AbilityGrenade.h"
#include "AbilitySlowTime.h"
#include "AbilityHeal.h"
#include "InputManager.h"

AbilityScript::AbilityScript(AbilityBase* ability)
{
	m_ability = ability;
}

AbilityScript::~AbilityScript()
{
	delete m_ability;
}

void AbilityScript::Update(double dt)
{
	if (!m_ability)
		return;
	if (!m_ability->IsInUse())
	{
		if (InputManager::GetInstance()->GetInputStrength("PlayerDodge"))
			m_ability->Use(this);
	}
	else/*if (m_ability->IsInUse())*/
	{
		m_ability->Update(this);
	}
}

float AbilityScript::GetPercentageCooldownDone()
{
	return m_ability->GetPercentageCooldownDone();
}