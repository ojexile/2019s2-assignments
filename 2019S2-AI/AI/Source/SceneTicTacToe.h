#ifndef SCENE_TICTACTOE_H
#define SCENE_TICTACTOE_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneTicTacToe : public SceneBase
{
	enum WHO_CONTENT
	{
		WHO_NONE = 0,
		WHO_CIRCLE,
		WHO_CROSS,

	};
	enum WIN_CONDITIONS 
	{
		/* TIC TAC TOE GRID NUMBERING IS AS FOLLOWS:
		2 | 5 | 8
		1 | 4 | 7
		0 | 3 | 6
		*/


		// horizontals
		C036,
		C147,
		C258,
		// verticals
		C012,
		C345,
		C678,
		// diagonals 
		C146,
		C048,

		C_COUNT
	};
public:
	SceneTicTacToe();
	~SceneTicTacToe();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	GameObject* FetchGO();

	int GetAIDecision();
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
	WHO_CONTENT m_grid[9];
	bool m_bCrossTurn;
	bool m_bGameOver;
	WHO_CONTENT m_winner;
	int m_wincondition[C_COUNT][2];
};

#endif