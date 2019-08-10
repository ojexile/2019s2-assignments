#pragma once
#include "KeyboardManager.h"
#include "InputBinding.h"
#include <map>

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;

	std::map<std::string, std::vector<InputBinding*>> bindings;
public:
	float GetInputStrength(std::string inputName);

	InputManager();

	void LoadBindings(std::string fileName);
	void ExportBindings(std::string fileName);
	void AddBinding(std::string bindName, InputBinding* bind);

};

