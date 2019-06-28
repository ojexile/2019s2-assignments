#ifndef SCENE_ASTEROID_H
#define SCENE_ASTEROID_H

#include "RenderingManagerBase.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include "GameObject.h"
#include "GameObjectManager.h"
#include "DataContainer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Locator.h"

#include <vector>
#include <sstream>

class RenderingManager : public RenderingManagerBase
{
	friend class Engine;
public:
	virtual void SetMouseCallback(GLFWwindow* window) override;
protected:
	RenderingManager();
	virtual ~RenderingManager();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render(Scene* scene);
	void RenderGameObject(GameObject* go);
	virtual void Exit();
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
};

#endif