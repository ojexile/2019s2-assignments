#include "ScoreScript.h"

ScoreScript::ScoreScript()
{
	m_iScore = 0;
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
}