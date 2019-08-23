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
#include "ColorFBO.h"

class RenderingManager : public RenderingManagerBase
{
	friend class Engine;
private:
	std::vector<GameObject*> RenderQueue;
	void RenderQueued(Scene* scene);
	ColorFBO Post;
	// unsigned m_RenderPass;
	unsigned m_PostBO;
	// unsigned m_FrameFBO;
public:
	virtual void SetMouseCallback(GLFWwindow* window) override;

	virtual void RenderPassGPass(Scene* scene);
	virtual void RenderPassPost(Scene* scene);
	virtual void RenderPassMain(Scene* scene);
	virtual void RenderWorld(Scene* scene);
	virtual void RenderPostQuad(Scene* scene);
	static Vector3 MouseWorldDir();
protected:
	RenderingManager();
	virtual ~RenderingManager();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render(Scene* scene);
	void RenderGameObject(GameObject* go, Vector3 vCamPos, bool bIsUI, bool first = true);
	virtual void Exit();
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
};

#endif