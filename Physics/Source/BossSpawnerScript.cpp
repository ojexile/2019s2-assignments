#include "BossSpawnerScript.h"
#include "SceneManager.h"
#include "Time.h"
BossSpawnerScript::BossSpawnerScript(GameObject * a, GameObject * b, GameObject * c)
	: m_iCurrentBoss(0)
{
	m_Boss[0] = a;
	m_Boss[1] = b;
	m_Boss[2] = c;

	m_fSpawnIntervals[0] = 100;
	m_fSpawnIntervals[1] = 1000000;
	m_fSpawnIntervals[2] = 1000000;

	m_fCurrentInterval = m_fSpawnIntervals[0];
	m_fSpawnRate = 1;
	m_CurrentTime = 0;
}

BossSpawnerScript::~BossSpawnerScript()
{
}

void BossSpawnerScript::Start()
{
	BossState = "Searching for player...";
}

void BossSpawnerScript::Update(double dt)
{
	m_CurrentTime += Time::GetInstance()->GetDeltaTimeF() * m_fSpawnRate;

	if (m_CurrentTime >= m_fCurrentInterval && m_iCurrentBoss < 2)
	{
		m_CurrentTime = 0;
		Vector3 Pos = SceneManager::GetInstance()->GetScene()->GetPlayer()->TRANS->GetPosition();
		Pos.x += 25;
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

void BossSpawnerScript::SetState(std::string state)
{
	BossState = state;
}

std::string BossSpawnerScript::GetState()
{
	return BossState;
}