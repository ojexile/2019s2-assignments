#pragma once
#include "Singleton.h"
class Time : public Singleton<Time>
{
private:
	double m_dDeltatime;
	double m_dElapsedtime;
public:
	Time();
	~Time();

	void Update(double dt);

	double GetDeltaTimeD();
	float GetDeltaTimeF();

	double GetElapsedTimeD();
	float GetElapsedTimeF();
};
