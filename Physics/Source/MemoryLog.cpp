#include "MemoryLog.h"

MemoryLog::MemoryLog()
{

}

std::map <void*, memoryRecord>& MemoryLog::getLog()
{
	return memLog;
}

void MemoryLog::createLog(void* mem, const char* File, const char* Func, int Line)
{
	
	memLog[mem] = memoryRecord(std::string(File), std::string(Func), std::to_string(Line));
}

void MemoryLog::removeLog(void* mem)
{
	memLog.erase(mem);
}

void MemoryLog::showLog()
{
	for (auto& iterator : memLog)
	{
		std::string tmp = iterator.second.fileName + " " + iterator.second.functionName + " " + iterator.second.lineNo + "\n";
		std::cout << tmp;
	}
}