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
	const SHORT m_Color;
	std::string m_sUser;
public:
	Logger(std::string sUser, SHORT Color);
	~Logger();

	void Log(std::string slog, std::string optional = "");
	int PrintLogs(int iYOffset);
};
