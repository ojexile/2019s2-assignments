#include "AbilityScript.h"
#include "AbilityDash.h"
#include "AbilityGrenade.h"
#include "AbilitySlowTime.h"
#include "AbilityHeal.h"
#include "InputManager.h"

AbilityScript::AbilityScript(AbilityBase* ability, GameObject* UI)
{
	m_ability = ability;
	m_UI = UI;
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

	float p = GetPercentageCooldownDone();
	if (p == 1)
	{
		m_UI->RENDER->SetAlpha(1.2f);
		m_UI->RENDER->SetColor(1.7f);
	}
	else
	{
		m_UI->RENDER->SetAlpha(p);
		m_UI->RENDER->SetColor(0.5f);
	}
}

float AbilityScript::GetPercentageCooldownDone()
{
	return m_ability->GetPercentageCooldownDone();
}