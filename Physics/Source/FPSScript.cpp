#include "FPSScript.h"
#include "Time.h"
#include <sstream>
#include "RenderComponent.h"
#define UPDATE_RATE 0.5f
FPSScript::FPSScript()
{
	m_fLastUpdate = 0;
}

FPSScript::~FPSScript()
{
}
void FPSScript::Start()
{
	m_rc = RENDER;
	m_rc->SetText(std::to_string(0));
}
void FPSScript::Update(double dt)
{
	m_iNumFrames++;
	float duration = Time::GetInstance()->GetElapsedTimeF() - m_fLastUpdate;
	if (duration >= UPDATE_RATE)
	{
		m_fLastUpdate = Time::GetInstance()->GetElapsedTimeF();
		m_rc = RENDER;
		float fps = m_iNumFrames / duration;
		// float fps = 1/ (float)dt;
		//int ifps = fps;
		//ifps /= 10;
		//ifps *= 10;
		std::stringstream ss;
		ss.precision(2);
		ss << fps;
		m_rc->SetText(ss.str());
		// m_rc->SetText(std::to_string(1 / dt));
		m_iNumFrames = 0;
		// CHENG_LOG("TIME: " + ss.str());
	}
}