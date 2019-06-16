#pragma once
#include "Renderer.h"
#include "RenderingManager.h"

#include "Scene.h"
#include "TestScene.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Init();
	void Update(double dt);
	void Exit();
private:
	static Renderer* m_Renderer;
	Scene* firstScene;
};
