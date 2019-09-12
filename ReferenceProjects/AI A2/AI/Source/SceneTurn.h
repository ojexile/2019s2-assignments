#ifndef SCENE_TURN_H
#define SCENE_TURN_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Maze.h"
#include <queue>

class SceneTurn : public SceneBase
{
public:
	SceneTurn();
	~SceneTurn();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	bool Handle(Message *message);
	void RenderGO(GameObject *go);
	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);

	void DFS(MazePt curr);
	void DFSlimit(GameObject* go, int limit);
	bool BFS(MazePt start, MazePt end);

	void DFSOnce(GameObject *go);
	bool BFSLimit(GameObject *go, MazePt end, int limit);
	bool AStar(GameObject* go, MazePt end);
	int cost_Estimate(MazePt start, MazePt end);
	bool RoomVisibilityCheck(GameObject* go);

	void GenerateStage(int noGrid);
	void ResetGame(int noGrid);
protected:
	int m_turn;
	double timer;

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;

	Maze m_maze;
	MazePt m_start;
	MazePt m_end;
	std::vector<Maze::TILE_CONTENT> m_myGrid; //read maze and store here
	std::vector<bool> m_visited; //visited set for DFS/BFS
	std::queue<MazePt> m_queue; //queue for BFS
	std::vector<MazePt> m_previous; //to store previous tile
	std::vector<MazePt> m_shortestPath;  //to store shortest path
	unsigned m_mazeKey;
	float m_wallLoad;

	GameObject* player;
	bool playerTurn;
	bool movingObjects;
	bool toggleMap;
	bool keyTaken;
	int stageNum;
};

#endif