#pragma once
#include "Renderer.h"
#include "RenderingManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "TestScene.h"

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
