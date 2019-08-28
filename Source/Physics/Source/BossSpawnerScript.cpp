#include "BossSpawnerScript.h"
#include "SceneManager.h"
#include "Time.h"
#include "EntityScript.h"
BossSpawnerScript::BossSpawnerScript(GameObject * a, GameObject * b, GameObject * c)
	: m_iCurrentBoss(0)
{
	m_Boss[0] = a;
	m_Boss[1] = b;
	m_Boss[2] = c;

	m_fSpawnIntervals[0] = 100;
	m_fSpawnIntervals[1] = 200;
	m_fSpawnIntervals[2] = 250;

	m_fCurrentInterval = m_fSpawnIntervals[0];
	m_fSpawnRate = 1;
	m_CurrentTime = 0;
}

BossSpawnerScript::~BossSpawnerScript()
{
}

void BossSpawnerScript::Start()
{
	m_eBossState = eSEARCHING;
}

void BossSpawnerScript::Update(double dt)
{
	m_CurrentTime += Time::GetInstance()->GetDeltaTimeF() * m_fSpawnRate;

	if (m_CurrentTime >= m_fCurrentInterval && m_iCurrentBoss < 2)
	{
		m_CurrentTime = 0;
		Vector3 Pos = SceneManager::GetInstance()->GetScene()->GetPlayer()->TRANS->GetPosition();
		Pos.x += 12;
		Instantiate(m_Boss[m_iCurrentBoss], Pos);
		++m_iCurrentBoss;
		m_fCurrentInterval = m_fSpawnIntervals[m_iCurrentBoss];
	}
}

float BossSpawnerScript::GetPercentageDone()
{
	return (m_CurrentTime / m_fCurrentInterval);
}

void BossSpawnerScript::SetSpawnRate(float f)
{
	m_fSpawnRate = f;
}

void BossSpawnerScript::SetState(BossSpawnerScript::eSearchState e)
{
	m_eBossState = e;
}

BossSpawnerScript::eSearchState BossSpawnerScript::GetState()
{
	return m_eBossState;
}

void BossSpawnerScript::ForceSpawn()
{
	if (m_iCurrentBoss >= 3)
		return;
	m_CurrentTime = 0;
	Vector3 Pos = SceneManager::GetInstance()->GetScene()->GetPlayer()->TRANS->GetPosition();
	Pos.x += 25;
	GameObject* boss = Instantiate(m_Boss[m_iCurrentBoss], Pos);
	boss->GetComponent<EntityScript>()->SetBoss();
	++m_iCurrentBoss;
	m_fCurrentInterval = m_fSpawnIntervals[m_iCurrentBoss];
}