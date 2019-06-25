#pragma once
#include "Renderer.h"
#include "RenderingManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "TestScene.h"

#include "Logger.h"
#include "Locator.h"
#include "WindowData.h"

class Engine
{
	friend class Application;
private:
	Engine();
	~Engine();

	void Init();
	void Update(double dt);
	void Exit();
	static Renderer* m_Renderer;
public:
};
