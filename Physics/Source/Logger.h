#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "LogData.h"
#include "WindowData.h"

class Logger
{
private:
	std::vector<LogData> m_vec_LogList;
public:
	Logger();
	~Logger();

	void Log(std::string);
	int PrintLogs(int iYOffset);
};
