#ifndef SCENE_KNIGHT_H
#define SCENE_KNIGHT_H

#include <vector>
#include "SceneBase.h"

class SceneKnight : public SceneBase
{
public:
	SceneKnight();
	~SceneKnight();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;
};

#endif