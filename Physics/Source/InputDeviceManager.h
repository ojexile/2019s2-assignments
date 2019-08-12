#pragma once
#include <string>


class InputDeviceManager
{
public:
	virtual float GetStrength(std::string bind) = 0;

};