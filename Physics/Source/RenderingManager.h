#ifndef SCENE_ASTEROID_H
#define SCENE_ASTEROID_H

#include "RenderingManagerBase.h"
#include "GL\glew.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "DataContainer.h"
#include "Scene.h"
#include "RenderComponent.h"

#include <vector>
#include <sstream>

class RenderingManager : public RenderingManagerBase
{
	friend class Engine;
public:
protected:
	RenderingManager();
	virtual ~RenderingManager();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render(Scene* scene);
	virtual void Exit();
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
};

#endif