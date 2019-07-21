#pragma once
#include "Singleton.h"
class Time : public Singleton<Time>
{
	friend class Singleton<Time>;
private:
	double m_dDeltatime;
	double m_dElapsedtime;
	Time();
	~Time();
public:

	void Update(double dt);

	//double GetDeltaTimeD();
	float GetDeltaTimeF();

	//double GetElapsedTimeD();
	float GetElapsedTimeF();
};
