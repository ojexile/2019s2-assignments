#ifndef SCENE_MOVEMENT2_H
#define SCENE_MOVEMENT2_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneMovementv2 : public SceneBase
{
public:
	SceneMovementv2();
	~SceneMovementv2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);
	void MoveAI();

	GameObject* FetchGO();
protected:

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;
	float m_hourOfTheDay;
};

#endif