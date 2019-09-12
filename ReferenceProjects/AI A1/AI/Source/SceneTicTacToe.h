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
		WHO_CROSS,
		WHO_CIRCLE,
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

	int GetAIDecision(WHO_CONTENT type);
	int minimax(WHO_CONTENT type, bool isMax);
	WHO_CONTENT checkWin();
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

	bool AiPlaying;
	bool firstTurn;
	float AiTimeLimiter;
	float AiTimer;
};

#endif