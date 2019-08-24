#include "ScalePatternScript.h"
#include "RenderComponent.h"

ScalePatternScript::ScalePatternScript(eScalePattern sp, float maxscale, float maxtime, float offset)
	: m_scalePattern(sp),
	m_fTimeElapsed(0.f),
	m_fMaximumScale(maxscale),
	m_fMaximumTimeElapsed(maxtime),
	m_fScaleOffset(offset),
	m_fGradient(- maxscale/maxtime)
{
}

ScalePatternScript::~ScalePatternScript()
{
}

void ScalePatternScript::Update(double dt)
{
	float currentscalarfactor = TRANS->GetScale().x;
	float newscalarfactor = 1;
	if (m_scalePattern == SHRINK)
	{
		newscalarfactor = m_fGradient * m_fTimeElapsed + m_fMaximumScale + m_fScaleOffset;

	}
	
	if (m_scalePattern == BREATHE)
	{
		newscalarfactor = m_fMaximumScale * sin(Math::PI * m_fTimeElapsed) + m_fScaleOffset;
	}
	
	if (newscalarfactor > 0.1f)
		currentscalarfactor = newscalarfactor;
	else
	{
		RENDER->SetActive(false);
	}

	TRANS->SetScale(currentscalarfactor);

	m_fTimeElapsed += (float)dt;
	if (m_fTimeElapsed > m_fMaximumTimeElapsed)
	{
		//DestroySelf();
	}
}


