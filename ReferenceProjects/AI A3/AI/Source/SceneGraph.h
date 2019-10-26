#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Maze.h"
#include <queue>
#include "Graph.h"

class SceneGraph : public SceneBase
{
public:
	SceneGraph();
	~SceneGraph();
	
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	bool Handle(Message *message);
	void RenderGO(GameObject *go);
	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);

	void RenderGraph();

	void GoRandomAdjacent(GameObject *go);
	void DFSOnce(GameObject *go);	void InitPath();
	void AssignPath(GameObject *go, int pathID);
	void SpawnTower(Vector3 position, GameObject::FACTIONS faction);
	void SpawnMinion(int path, GameObject::FACTIONS faction);
	//0 = Top(BLU), 1 = Mid(BLU), 2 = Bot(BLU), 3 = Top(RED), 4 = Mid(RED), 5 = Bot(RED)
	std::vector<std::vector<Node*>> m_paths;
protected:
	float nodeScaleSize;

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;

	int size;
	Graph m_graph;
	unsigned m_graphKey;

	float spawnTimer;
	float timer;
	int spawnCount;
	int enemySpawnCount;

	enum EnemyStrategy
	{
		ES_SPLIT,
		ES_RUSH
	};

	EnemyStrategy enemyStrategy;
	float spawnDelay;
	float spawnDelayTimer;

	int playerLifes;
	int enemyLifes;

	//0 = in game, 1 = win, 2 = lose
	int gameWon;
};

#endif