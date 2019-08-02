#pragma once
#include "Vector3.h"
#include "Singleton.h"
#include <fstream>
#include "Locator.h"
#include <string>
#include <sstream>
#include <map>

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
class Preferences
{
private:
	static std::map<std::string, std::string> m_map_Data;
	static void GetData();
	static void InitDefault();
	static bool m_bInitialsed;
	Preferences();
	~Preferences();
public:

	static std::string GetPref(std::string s);
	static void Clear();
};
