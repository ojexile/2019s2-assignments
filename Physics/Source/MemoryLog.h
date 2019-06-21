#pragma once
#include <string>
#include <map>
#include <iostream>

struct memoryRecord
{
public:
	memoryRecord() {};
	memoryRecord(std::string File, std::string Func, std::string Line) {this->fileName = File;	this->functionName = Func; this->lineNo = Line;}
	std::string fileName;
	std::string functionName;
	std::string lineNo;
};

class MemoryLog
{
public:
	MemoryLog();
	std::map<void*, memoryRecord>& getLog();
	void createLog(void* mem, const char* File, const char* Func, int Line);
	void removeLog(void* mem);
	void showLog();
private:
	std::map <void*, memoryRecord> memLog;
};