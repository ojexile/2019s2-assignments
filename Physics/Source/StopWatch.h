#pragma once
#include <ctime>
///--------------------------------------------------------------------------------
// \author 
// Hao Cheng
// \brief 
// A simple interface to use <ctime.h> to time code
// --------------------------------------------------------------------------------
class StopWatch
{
private:
	std::clock_t m_Start;
	float m_fTime;
public:
	StopWatch(bool started);
	StopWatch();
	~StopWatch();

	void Start();
	float Stop();
	float GetTime();
};

