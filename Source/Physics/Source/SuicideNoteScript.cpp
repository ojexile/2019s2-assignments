#include "SuicideNoteScript.h"

SuicideNoteScript::SuicideNoteScript(float fLifeTime)
	:m_fLifeTime(fLifeTime)
{
}

SuicideNoteScript::~SuicideNoteScript()
{
}

void SuicideNoteScript::Start()
{
	s.Start();
}

void SuicideNoteScript::Update(double dt)
{
	if (s.GetTime() >= m_fLifeTime)
		DestroySelf();
}