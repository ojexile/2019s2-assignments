#include "AbilityScript.h"
#include "AbilityDash.h"
#include "AbilityGrenade.h"
#include "AbilitySlowTime.h"
#include "AbilityHeal.h"
#include "InputManager.h"

AbilityScript::AbilityScript()
{
	//m_ability = new AbilityDash(3.f, 45.f);
	//m_ability = new AbilitySlowTime(3.f, 10.f, 75.f, 10.f);
	m_ability = new AbilityHeal(3.f, 30.f, 70.f, 30.f);
}

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
