#ifndef SCENE_ASTEROID_H
#define SCENE_ASTEROID_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneAsteroid : public SceneBase
{
public:
	SceneAsteroid();
	~SceneAsteroid();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
protected:

	//Physics
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
};

#endif