#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "Engine.h"
#include "Singleton.h"
#include <map>
#include <GLFW\glfw3.h>
#include "InputDeviceManager.h"

class KeyboardManager : public InputDeviceManager, public Singleton<KeyboardManager>
{
	friend Singleton<KeyboardManager>;
public:
	bool GetKeyTriggered(std::string bind);
	bool GetKeyTriggered(unsigned short key);
	bool GetKeyDown(std::string bind);
	bool GetKeyDown(unsigned short key);
	virtual float GetStrength(std::string bind);

private:
	std::map<std::string, unsigned int> map_keyBindings;
	std::map<unsigned int, bool> map_lastKeyPollState;
	KeyboardManager();
	~KeyboardManager();
};

#endif