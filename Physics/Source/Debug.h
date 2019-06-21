#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include "MemoryLog.h" 

static MemoryLog malloc_Log;

void* operator new(size_t size, const char* File, const char* Func, int Num)
{
	//Use tmp to ensure that the same thing is being reused instead
	//of multiple blocks of the same data but diff address is being used
	//printf("malloc called\n");
	
	void* tmp = nullptr;
	tmp = std::malloc(size);

	malloc_Log.createLog(tmp, File, Func, Num);
	
	return tmp;
}

void operator delete(void* ptr)
{
	//printf("free called\n");
	if (malloc_Log.getLog().size() != 0 &&
		malloc_Log.getLog().find(ptr) != malloc_Log.getLog().end())
	{
		malloc_Log.removeLog(ptr);
		std::free(ptr);
	}
}


void isMemLeaked()
{
	if (!malloc_Log.getLog().empty())
	{
		printf("Mem leak at the following locations\n");
		malloc_Log.showLog();
	}
	else
	{
		printf("no mem leak\n");
	}
}