#include "GoalScript.h"
#include "AudioManager.h"
GoalScript::GoalScript()
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

	AudioManager::GetInstance()->PlayBGM("pop.wav");

	CHENG_LOG("GOAL", std::to_string(m_iNumGoals));
}