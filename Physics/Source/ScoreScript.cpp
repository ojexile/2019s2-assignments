#include "ScoreScript.h"
#include "RenderComponent.h"
int ScoreScript::m_iScore = 0;

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
void ScoreScript::Update(double dt)
{
	RenderComponent* rc = GetComponent<RenderComponent>();
	rc->SetText("Score: " + std::to_string(m_iScore));
}