#pragma once
#include <ctime>
#include <string>

#define START StopWatch s(true)
#define STOP_S s.Stop()->GetSTime()
#define STOP_F s.Stop()->GetTime()

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
	StopWatch* Stop();
	float GetTime();
	std::string GetSTime();
	void Reset();
};

