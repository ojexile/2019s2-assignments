#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "Engine.h"
#include "Singleton.h"
#include <map>
#include <GLFW\glfw3.h>

class KeyboardManager : public Singleton<KeyboardManager>
{
	friend Singleton<KeyboardManager>;
public:
	bool GetKeyTriggered(std::string bind);
	bool GetKeyTriggered(unsigned short key);
	bool GetKeyDown(std::string bind);
	bool GetKeyDown(unsigned short key);
	void SetKeyBind(std::string bind, unsigned short key);
	void LoadKeyBinds(std::string filename);
	void ExportKeyBinds(std::string filename);

private:
	std::map<std::string, unsigned int> map_keyBindings;
	std::map<unsigned int, bool> map_lastKeyPollState;
	KeyboardManager();
	~KeyboardManager();
};

#endif