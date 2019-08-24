#include "BossSpawnerScript.h"
#include "SceneManager.h"
BossSpawnerScript::BossSpawnerScript(GameObject * a, GameObject * b, GameObject * c)
	: m_iCurrentBoss(0)
{
	m_Boss[0] = a;
	m_Boss[1] = b;
	m_Boss[2] = c;

	m_fSpawnIntervals[0] = 5;
	m_fSpawnIntervals[1] = 1000000;
	m_fSpawnIntervals[2] = 1000000;

	m_fCurrentInterval = m_fSpawnIntervals[0];
}

BossSpawnerScript::~BossSpawnerScript()
{
}

void BossSpawnerScript::Start()
{
	s.Start();
}

void BossSpawnerScript::Update(double dt)
{
	if (s.GetTime() >= m_fCurrentInterval && m_iCurrentBoss < 2)
	{
		s.Reset();
		Vector3 Pos = SceneManager::GetInstance()->GetScene()->GetPlayer()->TRANS->GetPosition();
		Pos.x += 25;
		Instantiate(m_Boss[m_iCurrentBoss], Pos);
		++m_iCurrentBoss;
		m_fCurrentInterval = m_fSpawnIntervals[m_iCurrentBoss];
	}
}

float BossSpawnerScript::GetPercentageDone()
{
	return (s.GetTime() / m_fCurrentInterval);
}