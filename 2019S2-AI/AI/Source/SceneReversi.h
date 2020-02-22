#ifndef SCENE_REVERSI_H
#define SCENE_REVERSI_H

#include <vector>
#include "SceneBase.h"

class SceneReversi : public SceneBase
{
	enum WHO_CONTENT
	{
		WHO_NONE = 0,
		WHO_BLACK,
		WHO_WHITE,
	};
public:
	SceneReversi();
	~SceneReversi();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	bool Move(std::vector<WHO_CONTENT>& grid, bool black, int index);
	int Count(std::vector<WHO_CONTENT>& grid, bool black);
	bool CheckGotMove(std::vector<WHO_CONTENT>& grid, bool black);
	int GetAIDecision(std::vector<WHO_CONTENT>& grid, bool black);
	int MinMax(std::vector<WHO_CONTENT>& grid, bool black, bool max, bool depth);

	void Reset();

protected:

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;

	std::vector<WHO_CONTENT> m_grid;
	bool m_bBlackTurn;
	bool m_bGameOver;
	WHO_CONTENT m_winner;
	int m_black, m_white;
};

#endif