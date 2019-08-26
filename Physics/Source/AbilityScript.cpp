#include "AbilityScript.h"
#include "AbilityDash.h"
#include "InputManager.h"

AbilityScript::AbilityScript()
{
	m_ability = new AbilityDash(10.f, 45.f);


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
		if (m_ability->CanUse())
			m_ability->Use(this);
	}
	if (m_ability->IsInUse())
	{

		m_ability->Update(this);
	}

}
