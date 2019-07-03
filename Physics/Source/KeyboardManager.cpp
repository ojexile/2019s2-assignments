#include "KeyboardManager.h"

#include <windows.h>
#include <fstream>

KeyboardManager::KeyboardManager()
{
	SetKeyBind("ExitGame", VK_ESCAPE);
	LoadKeyBinds("keybinds.cfg");
}


KeyboardManager::~KeyboardManager()
{
}


bool KeyboardManager::GetKeyTriggered(std::string bind)
{
	if (map_keyBindings.count(bind) == 0)
	{
		KZ_LOG("Tried to poll state of nonexistent/undefined keybind " + bind);
		return false;
	}
	bool lastState = map_lastKeyPollState[map_keyBindings[bind]];
	map_lastKeyPollState[map_keyBindings[bind]] = GetKeyDown(bind);
	return GetKeyDown(map_keyBindings[bind]) && !lastState;
}

bool KeyboardManager::GetKeyTriggered(unsigned short key)
{
	bool lastState = map_lastKeyPollState[key];
	map_lastKeyPollState[key] = GetKeyDown(key);
	return GetKeyDown(key) && !lastState;
}


bool KeyboardManager::GetKeyDown(std::string bind)
{
	if (map_keyBindings.count(bind) == 0)
	{
		KZ_LOG("Tried to poll state of nonexistent/undefined keybind " + bind);
		return false;
	}
		
	return GetKeyDown(map_keyBindings[bind]);
}

bool KeyboardManager::GetKeyDown(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

void KeyboardManager::SetKeyBind(std::string bind, unsigned short key)
{
	map_keyBindings[bind] = key;
}

void KeyboardManager::LoadKeyBinds(std::string filename)
{
	std::ifstream stream = std::ifstream(filename);
	if (stream.is_open())
	{
		while (!stream.eof())
		{
			std::string bind;
			int key;
			stream >> bind;
			stream >> key;
			SetKeyBind(bind, key);
		}
		stream.close();
	}
	else
	{
		KZ_LOG("Tried to load keybinds from nonexistent file (\"" + filename + "\"");
	}
}
void KeyboardManager::ExportKeyBinds(std::string filename)
{
	std::ofstream stream = std::ofstream(filename);
	if (stream.is_open())
	{
		for (auto it = map_keyBindings.begin(); it != map_keyBindings.end(); it++)
		{
			stream << it->first << " " << it->second << "\n";
		}
		stream.close();
	}
}