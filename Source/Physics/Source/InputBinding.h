#pragma once
#include <string>
#include "InputDeviceManager.h"

class InputBinding
{
	float strength;
	std::string bindingCode;
	InputDeviceManager* device;
public:
	InputBinding(std::string bindingString, float strength);
	float GetCurrentStrength();
};