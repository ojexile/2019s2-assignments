#pragma once
#include "Vector3.h"
#include "Singleton.h"
#include <fstream>
#include "Locator.h"
#include <string>
#include <sstream>

// read from a file of format
// term = value
// terms
// windowSize
// windowPosition
// consoleSize
// consolePosition
// fontSize
// Value format
// x,y
class Preferences : public Singleton<Preferences>
{
private:
	Vector3 m_vWindowSize;
	Vector3 m_vConsoleSize;
	Vector3 m_vWindowPosition;
	Vector3 m_vConsolePosition;
	Vector3 m_vFontSize;
public:
	Preferences();
	~Preferences();

	void GetData();

	Vector3 GetWindowSize();
	Vector3 GetConsoleSize();
	Vector3 GetConsolePosition();
	Vector3 GetWindowPosition();
	Vector3 GetFontSize();
};
