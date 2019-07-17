#include "Time.h"

Time::Time()
{
	m_dDeltatime = 0;
	m_dElapsedtime = 0;
}

Time::~Time()
{
}
void Time::Update(double dt)
{
	m_dDeltatime = dt;
	m_dElapsedtime += dt;
}

double Time::GetDeltaTimeD()
{
	return m_dDeltatime;
}
float Time::GetDeltaTimeF()
{
	return (float)m_dDeltatime;
}

double Time::GetElapsedTimeD()
{
	return m_dElapsedtime;
}
float Time::GetElapsedTimeF()
{
	return (float)m_dElapsedtime;
}