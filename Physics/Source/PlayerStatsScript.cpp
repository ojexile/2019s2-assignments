#include "PlayerStatsScript.h"



PlayerStatsScript::PlayerStatsScript(GameObject* Player, GameObject* Stamina, GameObject* Health)
	: m_Player(Player)
	, m_Stamina(Stamina)
	, m_Health(Health)
{
	m_fStamina = 50;
	m_fHealth = 100;
}


PlayerStatsScript::~PlayerStatsScript()
{
}
void PlayerStatsScript::Update(double dt)
{
	m_fStamina += (float)dt * 10;
	m_fStamina = Math::Clamp(m_fStamina, 0.f, 100.f);
	m_Stamina->TRANS->SetScale(m_fStamina / 100 * 200, 50, 1);

	m_Health->TRANS->SetScale(m_fHealth / 100 * 200, 50, 1);

}
float PlayerStatsScript::GetStamina()
{
	return m_fStamina;
}
void PlayerStatsScript::DrainStamina(float f)
{
	m_fStamina -= f;
}