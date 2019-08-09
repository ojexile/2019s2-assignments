#pragma once
#include "Renderer.h"
#include "RenderingManager.h"
#include "LightManager.h"
#include "SceneManager.h"

#include "Scene.h"

#include "Logger.h"
#include "Locator.h"
#include "Preferences.h"

#include "CollisionManager.h"

#include <vector>

//#define LOG_UPDATE_RATE 1

class Engine
{
	friend class Application;
public:
	void SetMouseCallback(GLFWwindow* window);
private:
	Engine();
	~Engine();
	float m_fLogUpdateTimer;
	void Init();
	void Update(double dt);
	void Exit();
	static Renderer* m_Renderer;
	CollisionManager m_CollisionManager;
public:
};
