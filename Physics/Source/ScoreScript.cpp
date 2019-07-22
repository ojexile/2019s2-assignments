#include "ScoreScript.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "RojakScene2.h"

#define MAX_DESTRUCT 4

int ScoreScript::m_iScore = 0;
int ScoreScript::m_iDestroyed = 0;
int ScoreScript::m_iCurrentLevel = 0;

ScoreScript::ScoreScript()
{
}

ScoreScript::~ScoreScript()
{
}
void ScoreScript::IncrementScore(int i)
{
	m_iScore += i;
}
void ScoreScript::ObjectDestroyed()
{
	m_iDestroyed += 1;
}
void ScoreScript::Update(double dt)
{
	RenderComponent* rc = GetComponent<RenderComponent>();
	rc->SetText("Score: " + std::to_string(m_iScore));
	if (MAX_DESTRUCT == m_iDestroyed)
	{
		switch (m_iCurrentLevel)
		{
		case 0:
			SceneManager::GetInstance()->ChangeScene(new RojakScene2);
				break;
		default:
			break;
		}
		++m_iCurrentLevel;
	}
}