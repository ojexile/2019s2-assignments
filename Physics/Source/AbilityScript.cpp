#include "AbilityScript.h"
#include "AbilityDash.h"
#include "AbilityGrenade.h"
#include "InputManager.h"

AbilityScript::AbilityScript()
{
	//m_ability = new AbilityDash(3.f, 45.f);
	m_ability = new AbilityGrenade(10.f, 75.f);

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
	if (InputManager::GetInstance()->GetInputStrength("PlayerDodge"))
	{
		if (!m_ability->IsInUse())
			m_ability->Use(this);
	}
	if (m_ability->IsInUse())
	{
		m_ability->Update(this);
	}

}
