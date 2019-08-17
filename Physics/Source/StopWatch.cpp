#include "StopWatch.h"
#include <sstream>

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
StopWatch* StopWatch::Stop()
{
	m_fTime = static_cast<float>((std::clock() - m_Start) / (double)CLOCKS_PER_SEC);
	return this;
}
float StopWatch::GetTime()
{
	return m_fTime;
}
std::string StopWatch::GetSTime()
{
	std::stringstream ss;
	ss.precision(3);
	ss << m_fTime;
	return ss.str();
}
void StopWatch::Reset()
{
	m_Start = std::clock();
	m_fTime = -1;
}