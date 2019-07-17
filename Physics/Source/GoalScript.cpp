#include "GoalScript.h"
#include "AudioManager.h"
GoalScript::GoalScript(ScoreScript* ScoreScript)
	: m_ScoreScript(ScoreScript)
{
	m_iNumGoals = 0;
}

GoalScript::~GoalScript()
{
}

void GoalScript::Update(double dt)
{
}
void GoalScript::Collide(GameObject* go)
{
	++m_iNumGoals;
	Destroy(go);
	m_ScoreScript->IncrementScore(-10);
	AudioManager::GetInstance()->Play3D("pop.wav", {});

	CHENG_LOG("GOAL", std::to_string(m_iNumGoals));
}