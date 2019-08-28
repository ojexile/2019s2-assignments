#pragma once
#include "InputDeviceManager.h"
#include "Singleton.h"

class MouseManager : public InputDeviceManager, public Singleton<MouseManager>
{
	friend Singleton<MouseManager>;
	float lastX, lastY, lastScrollX, lastScrollY;
	bool lastLMB, lastRMB;
public:
	virtual float GetStrength(std::string bind);
	MouseManager();
};