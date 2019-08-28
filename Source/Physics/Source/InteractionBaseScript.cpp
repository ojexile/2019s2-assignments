#include "InteractionBaseScript.h"

InteractionBaseScript::InteractionBaseScript()
	: m_bIsTriggered(false),
	m_fTimeElapsed(0.f),
	m_fMaximumTimeElapsed(-1.f)
{

}

InteractionBaseScript::~InteractionBaseScript()
{
}

void InteractionBaseScript::SetMaxElapsedTime(float maxtime)
{
	m_fMaximumTimeElapsed = maxtime;
}

bool InteractionBaseScript::IsAlreadyTriggered()
{
	return m_bIsTriggered;
}
