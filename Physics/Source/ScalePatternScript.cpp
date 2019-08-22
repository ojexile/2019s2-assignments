#include "ScalePatternScript.h"

ScalePatternScript::ScalePatternScript(eScalePattern sp, float maxscale, float maxtime)
	: m_scalePattern(sp),
	m_fTimeElapsed(0.f),
	m_fMaximumScale(maxscale),
	m_fMaximumTimeElapsed(maxtime)
{
}

ScalePatternScript::~ScalePatternScript()
{
}

void ScalePatternScript::Update(double dt)
{
	if (m_scalePattern == SHRINK)
	{
		float currentscalarfactor = 
	}
}


