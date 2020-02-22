#ifndef SCENE_QUEEN_H
#define SCENE_QUEEN_H

#include <vector>
#include "SceneBase.h"

class SceneQueen : public SceneBase
{
public:
	SceneQueen();
	~SceneQueen();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void PrintSolution();
	bool CheckQueen();
	void DFS(int row);

protected:

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;

	// container to store queens
	std::vector<int> m_queen;
	int m_numSolutions;
};

#endif