#include "Print.h"

Print::Print()
{
}

Print::~Print()
{
}

void Print::PrintLn(std::string s)
{
	std::cout << s;
	std::cout << std::endl;
}