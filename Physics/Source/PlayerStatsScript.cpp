#include "PlayerStatsScript.h"
#include "GunScript.h"
#include "PlayerScript.h"
#include "BossSpawnerScript.h"

PlayerStatsScript::PlayerStatsScript(GameObject* Player, GameObject* Stamina,
	GameObject* Health, GameObject* Gun, GameObject* BulletRef, GameObject* BossSpawner,
	GameObject* BossSpawnerUI)
	: m_Player(Player)
	, m_Stamina(Stamina)
	, m_Health(Health)
	, m_Gun(Gun)
	, m_BulletUIRef(BulletRef)
	, m_BossSpawner(BossSpawner)
	, m_BossSpawnerUI(BossSpawnerUI)
{
	m_iMaxMag = 0;
	m_iMag = 0;
}

void PlayerStatsScript::Start()
{
	m_iMaxMag = m_Gun->GetComponent<GunScript>()->GetMaxMagazineRounds();
	m_iMag = m_Gun->GetComponent<GunScript>()->GetMagazineRounds();
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
	for (int i = 0; i < m_Gun->GetComponent<GunScript>()->GetMaxMagazineRounds(); ++i)
	{
		Vector3 Pos = vStartPos + Vector3{ 0, i * fOffset, 0 };
		m_BulletList.push_back(Instantiate(m_BulletUIRef, Pos, "UI"));
	}
}
void PlayerStatsScript::UpdateBulletUI()
{
	int iNewMaxMag = m_Gun->GetComponent<GunScript>()->GetMaxMagazineRounds();
	if (iNewMaxMag != m_iMaxMag)
	{
		InitBulletUI();
	}
	m_iMaxMag = m_Gun->GetComponent<GunScript>()->GetMaxMagazineRounds();
	m_iMag = m_Gun->GetComponent<GunScript>()->GetMagazineRounds();
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
	PlayerScript* ps = m_Player->GetComponent<PlayerScript>();
	float fHealth = ps->GetValues()->GetHealth();
	float fStamina = ps->GetValues()->GetStamina();

	const Stats* Base = ps->GetBaseStats();
	const Stats* Add = ps->GetAdditionalStats();
	m_Stamina->TRANS->SetScale(fStamina / (Base->GetMaxStamina() * Add->GetMaxStamina()) * 200, 50, 1);
	// CHENG_LOG(std::to_string(fHealth));
	m_Health->TRANS->SetScale(fHealth / (Base->GetMaxHealth() * Add->GetMaxHealth()) * 200, 50, 1);
	float percen = m_BossSpawner->GetComp(BossSpawnerScript)->GetPercentageDone();
	m_BossSpawnerUI->TRANS->SetScale(percen * 1920 / 3, 12, 1);

	UpdateBulletUI();
}