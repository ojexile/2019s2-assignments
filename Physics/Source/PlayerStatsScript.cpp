#include "PlayerStatsScript.h"
#include "WeaponScript.h"
#include "PlayerScript.h"

PlayerStatsScript::PlayerStatsScript(GameObject* Player, GameObject* Stamina, 
	GameObject* Health, GameObject* Gun, GameObject* BulletRef)
	: m_Player(Player)
	, m_Stamina(Stamina)
	, m_Health(Health)
	, m_Gun(Gun)
	, m_BulletUIRef(BulletRef)
{
	m_fStamina = 50;
	m_iMaxMag = 0;
	m_iMag = 0;
}

void PlayerStatsScript::Start()
{
	m_iMaxMag = m_Gun->GetComponent<WeaponScript>()->GetMaxMagazineRounds();
	m_iMag = m_Gun->GetComponent<WeaponScript>()->GetMagazineRounds();
	InitBulletUI();
}
void PlayerStatsScript::InitBulletUI()
{
	Vector3 vStartPos = { 30,900,0 };
	float fOffset = -25;
	if (m_BulletList.size() > 0)
	{
		for (int i = 0; i < m_iMaxMag; ++i)
		{
			Destroy(m_BulletList.at(i));
		}
	}
	m_BulletList.clear();
	for (int i = 0; i < m_Gun->GetComponent<WeaponScript>()->GetMaxMagazineRounds(); ++i)
	{
		Vector3 Pos = vStartPos + Vector3{0, i * fOffset, 0};
		m_BulletList.push_back(Instantiate(m_BulletUIRef, Pos, "UI"));
	}
}
void PlayerStatsScript::UpdateBulletUI()
{
	int iNewMaxMag = m_Gun->GetComponent<WeaponScript>()->GetMaxMagazineRounds();
	if (iNewMaxMag != m_iMaxMag)
	{
		InitBulletUI();
	}
	m_iMaxMag = m_Gun->GetComponent<WeaponScript>()->GetMaxMagazineRounds();
	m_iMag = m_Gun->GetComponent<WeaponScript>()->GetMagazineRounds();
	for (int i = 0; i < m_iMaxMag; ++i)
	{
		if (i < m_iMag)
			m_BulletList.at(i)->SetActive(true);
		else
			m_BulletList.at(i)->SetActive(false);

	}
}
PlayerStatsScript::~PlayerStatsScript()
{
}
void PlayerStatsScript::Update(double dt)
{
	float fHealth = m_Player->GetComponent<PlayerScript>()->GetHealth();
	m_fStamina += (float)dt * 10;
	m_fStamina = Math::Clamp(m_fStamina, 0.f, 100.f);
	m_Stamina->TRANS->SetScale(m_fStamina / 100 * 200, 50, 1);

	// CHENG_LOG(std::to_string(fHealth));
	m_Health->TRANS->SetScale(fHealth / 100 * 200, 50, 1);
	
	UpdateBulletUI();
}
float PlayerStatsScript::GetStamina()
{
	return m_fStamina;
}
void PlayerStatsScript::DrainStamina(float f)
{
	m_fStamina -= f;
}