#include "InputManager.h"

float InputManager::GetInputStrength(std::string inputName)
{
	if (bindings.count(inputName) == 0)
		return 0;
	float currentTotalStrength = 0;
	for (auto it = bindings[inputName].begin(); it != bindings[inputName].end(); ++it)
	{
		currentTotalStrength += (*it)->GetCurrentStrength();
	}
	return currentTotalStrength;
}

InputManager::InputManager()
{
	LoadBindings(Resources::Path::Keybinds);
}

InputManager::~InputManager()
{
	for (auto it = bindings.begin(); it != bindings.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			delete *it2;
		}
	}
}

void InputManager::LoadBindings(std::string fileName)
{
	std::ifstream stream = std::ifstream(fileName);
	if (stream.is_open())
	{
		while (!stream.eof())
		{
			std::string bind;
			std::string keyString;
			float strength;
			stream >> bind;
			stream >> keyString;
			stream >> strength;
			bindings[bind].push_back(new InputBinding(keyString, strength));
		}
		stream.close();
	}
	else
	{
		KZ_LOG("Tried to load keybinds from nonexistent file (\"" + fileName + "\"");
	}
}
void InputManager::ExportBindings(std::string fileName)
{

}
void InputManager::AddBinding(std::string bindName, InputBinding* bind)
{

}