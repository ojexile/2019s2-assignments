#ifndef SCENE_MOVEMENT_H
#define SCENE_MOVEMENT_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneMovement : public SceneBase
{
public:
	SceneMovement();
	~SceneMovement();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);
	virtual bool Handle(Message *msg);

	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);
protected:

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	float m_hourOfTheDay;
	float timerHarvester;
	float timerPatroller;
	float timerEnemy;
	float timerRepairer;

	int destroyedCount;
	int repairerCount;
	int enemyCount;
};

#endif