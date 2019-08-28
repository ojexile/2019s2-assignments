#include "InputBinding.h"
#include "KeyboardManager.h"
#include "MouseManager.h"

InputBinding::InputBinding(std::string string, float strength)
{
	bindingCode = string.substr(string.find_first_of(":") + 1);
	if (string.substr(0, string.find_first_of(":")) == "keyboard")
	{
		device = KeyboardManager::GetInstance();
	}
	if (string.substr(0, string.find_first_of(":")) == "mouse")
	{
		device = MouseManager::GetInstance();
	}
	this->strength = strength;
}

float InputBinding::GetCurrentStrength()
{
	return device->GetStrength(bindingCode) * strength;
}