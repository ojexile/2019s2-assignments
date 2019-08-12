#include "StopWatch.h"

StopWatch::StopWatch()
{
}
StopWatch::StopWatch(bool started)
{
	if (started)
		Start();
}
StopWatch::~StopWatch()
{
}

void StopWatch::Start()
{
	m_Start = std::clock();
}
float StopWatch::Stop()
{
	m_fTime = static_cast<float>((std::clock() - m_Start) / (double)CLOCKS_PER_SEC);
	return m_fTime;
}
float StopWatch::GetTime()
{
	return m_fTime;
}