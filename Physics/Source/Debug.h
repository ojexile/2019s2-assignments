#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

extern void* operator new(size_t size, const char* File, const char* Func, int Num);
extern void operator delete(void* ptr);
extern void isMemLeaked();