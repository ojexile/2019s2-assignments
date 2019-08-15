#include "KeyboardManager.h"

#include <windows.h>
#include <fstream>
#include "Resources.h"

KeyboardManager::KeyboardManager()
{
}

KeyboardManager::~KeyboardManager()
{
}


unsigned short ToKey(std::string str)
{
	if (str.substr(0, 2) == "kc")
	{
		return std::stoi(str.substr(2));
	}
	if (str.length() == 1 && isalnum(str[0]))
	{
		return toupper(str[0]);
	}
	for (unsigned i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	if (str == "-") return VK_OEM_MINUS;
	if (str == "+") return VK_OEM_PLUS;
	if (str == "tab") return VK_TAB;
	if (str == "lshift") return VK_LSHIFT;
	if (str == "rshift") return VK_RSHIFT;
	if (str == "lctrl") return VK_LCONTROL;
	if (str == "rctrl") return VK_RCONTROL;
	if (str == "space") return VK_SPACE;
	if (str == "esc") return VK_ESCAPE;
	return NULL;
}


bool KeyboardManager::GetKeyTriggered(unsigned short key)
{
	bool lastState = map_lastKeyPollState[key];
	map_lastKeyPollState[key] = GetKeyDown(key);
	return GetKeyDown(key) && !lastState;
}

bool KeyboardManager::GetKeyDown(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool KeyboardManager::GetKeyTriggered(std::string bind)
{
	if (ToKey(bind) == NULL) return false;
	return GetKeyTriggered(ToKey(bind));
}

bool KeyboardManager::GetKeyDown(std::string bind)
{
	if (ToKey(bind) == NULL) return false;
	return GetKeyDown(ToKey(bind));
}

float KeyboardManager::GetStrength(std::string bind)
{
	if (bind.length() > 4 && bind.substr(bind.length() - 5) == "_down")
		if (GetKeyTriggered(bind.substr(0, bind.length() - 5))) return 1;
		else return 0;
	if (GetKeyDown(bind)) return 1;
	else return 0;
}