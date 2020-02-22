#ifndef SCENE_MAZE_H
#define SCENE_MAZE_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Maze.h"

class SceneMaze : public SceneBase
{
public:
	SceneMaze();
	~SceneMaze();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);
	GameObject* FetchGO();

	void DFS(MazePt curr);
	void BFS(MazePt start, MazePt end);

protected:

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;

	Maze m_maze;
	MazePt m_start, m_end;

	std::vector<Maze::TILE_CONTENT> m_myGrid; // personal memory for reading maze
	std::vector<bool> m_visited;
	std::vector<MazePt> m_queue; // queue for BFS
	std::vector<MazePt> m_previous; //to store shortest path
	unsigned m_mazeKey;
};

#endif