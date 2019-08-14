#include "StaminaScript.h"

StaminaScript::StaminaScript(GameObject* stam)
{
	m_Stam = stam;
	m_fStamina = 50;
}

StaminaScript::~StaminaScript()
{
}
void StaminaScript::Update(double dt)
{
	m_fStamina += dt * 40;
	m_fStamina = Math::Clamp(m_fStamina, 0.f, 100.f);
	m_Stam->TRANS->SetScale(m_fStamina / 100 * 200, 50, 1);
}
void StaminaScript::DrainStamina(float f)
{
	m_fStamina -= f;
}
float StaminaScript::GetStamina()
{
	return m_fStamina;
}