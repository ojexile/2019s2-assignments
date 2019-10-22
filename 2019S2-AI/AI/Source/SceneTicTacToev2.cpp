#include "SceneTicTacToev2.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneTicTacToev2::SceneTicTacToev2()
{
}

SceneTicTacToev2::~SceneTicTacToev2()
{
}

void SceneTicTacToev2::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;
	m_noGrid = 3;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2;

	firstTurn = true;
	m_bCrossTurn = Math::RandIntMinMax(0, 1);
	m_bGameOver = false;
	m_winner = WHO_CONTENT::WHO_NONE;
	AiTimeLimiter = 1;
	AiTimer = 0;
}

GameObject* SceneTicTacToev2::FetchGO()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
		{
			go->active = true;
			++m_objectCount;
			return go;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_CROSS);
		m_goList.push_back(go);
	}
	return FetchGO();
}

void SceneTicTacToev2::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	if (Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}
	if (Application::IsKeyPressed('R'))
	{
		//Exercise: Implement Reset button
		for (int i = 0; i < 9; ++i)
		{
			m_grid[i] = WHO_NONE;
		}
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end();)
		{
			it = m_goList.erase(it);
		}

		m_objectCount = 0;
		firstTurn = true;
		m_bCrossTurn = Math::RandIntMinMax(0, 1);
		m_bGameOver = false;
		m_winner = WHO_CONTENT::WHO_NONE;
		AiTimeLimiter = 1;
		AiTimer = 0;
	}

	//Input Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0) && m_bGameOver == false && !AiPlaying)
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
		//Exercise: Game inputs
		int gridX = posX / m_gridSize;
		int gridY = posY / m_gridSize;

		if (firstTurn == true)
		{
			firstTurn = false;
		}

		if (m_grid[gridY * 3 + gridX] == WHO_NONE)
		{
			GameObject* go = FetchGO();

			go->pos.Set(gridX * 33 + m_gridOffset, gridY * 33 + m_gridOffset, 0);
			go->scale.Set(m_gridSize * 0.5f, m_gridSize * 0.5f, 1);

			if (m_bCrossTurn == true)
			{
				go->type = GameObject::GO_CROSS;
				m_bCrossTurn = false;
				m_grid[gridY * 3 + gridX] = WHO_CROSS;
			}
			else
			{
				go->type = GameObject::GO_CIRCLE;
				m_bCrossTurn = true;
				m_grid[gridY * 3 + gridX] = WHO_CIRCLE;
			}

			for (int col = 2; col >= 0; --col)
			{
				for (int row = 0; row < 3; ++row)
				{
					std::cout << m_grid[row + col * 3];
				}
				std::cout << std::endl;
			}
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

	static bool bSpaceState = false;
	if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = true;
		if (AiPlaying == false)
		{
			AiPlaying = true;
		}
		else
		{
			AiPlaying = false;
		}
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}

	AiTimer += (float)dt;

	//If player AI takes over
	if (AiPlaying && m_bCrossTurn && AiTimer > AiTimeLimiter && m_objectCount < 8)
	{
		int AiInput;
		if (firstTurn == true)
		{
			AiInput = Math::RandIntMinMax(0, 8);
			firstTurn = false;
		}
		else
		{
			AiInput = GetAIDecision(WHO_CROSS);
		}

		int gridX, gridY;

		if (AiInput >= 6)
		{
			gridY = 2;
			gridX = AiInput - 6;
		}
		else if (AiInput >= 3)
		{
			gridY = 1;
			gridX = AiInput - 3;
		}
		else
		{
			gridY = 0;
			gridX = AiInput;
		}

		GameObject* go = FetchGO();
		go->pos.Set(gridX * 33 + m_gridOffset, gridY * 33 + m_gridOffset, 0);
		go->scale.Set(m_gridSize * 0.5f, m_gridSize * 0.5f, 1);
		go->type = GameObject::GO_CROSS;

		m_bCrossTurn = false;
		m_grid[AiInput] = WHO_CROSS;
		AiTimer = 0;
	}

	//Circle AI
	if (!m_bCrossTurn && AiTimer > AiTimeLimiter && m_objectCount < 8)
	{
		//Exercise: Call GetAIDecision() and put circle on grid
		int AiInput;
		if (firstTurn == true)
		{
			AiInput = Math::RandIntMinMax(0, 8);
			firstTurn = false;
		}
		else
		{
			AiInput = GetAIDecision(WHO_CIRCLE);
		}
	
		int gridX, gridY;

		if (AiInput >= 6)
		{
			gridY = 2;
			gridX = AiInput - 6;
		}
		else if (AiInput >= 3)
		{
			gridY = 1;
			gridX = AiInput - 3;
		}
		else
		{
			gridY = 0;
			gridX = AiInput;
		}
		
		GameObject* go = FetchGO();
		go->pos.Set(gridX * 33 + m_gridOffset, gridY * 33 + m_gridOffset, 0);
		go->scale.Set(m_gridSize * 0.5f, m_gridSize * 0.5f, 1);
		go->type = GameObject::GO_CIRCLE;

		m_bCrossTurn = true;
		m_grid[AiInput] = WHO_CIRCLE;
		AiTimer = 0;
	}

	//Game Logic Section
	//Exercise: Check draw, cross wins or circle wins
	m_winner = checkWin();
	if (m_winner != WHO_NONE)
		m_bGameOver = true;
	if (m_objectCount >= 8 && m_winner == WHO_NONE)
	{
		m_bGameOver = true;
	}
}

//Exercise: This function should return 0 to 8, i.e. AI player's decision to put circle on one of the grids
int SceneTicTacToev2::GetAIDecision(WHO_CONTENT type)
{
	int bestVal = -1000;
	int bestMove = -1;

	for (int i = 0; i < 9; ++i)
	{
		// Check if cell is empty 
		if (m_grid[i] == WHO_NONE)
		{
			// Make the move 
			m_grid[i] = type;

			// compute evaluation function for this 
			// move. 
			int moveVal = minimax(type, false);

			// Undo the move 
			m_grid[i] = WHO_NONE;

			if (moveVal > bestVal)
			{
				bestMove = i;
				bestVal = moveVal;
			}
		}
	}

	return bestMove;
}

int SceneTicTacToev2::minimax(WHO_CONTENT type, bool isMax)
{
	//Win
	if (checkWin() == type)
		return 10;

	//Lose
	else if (checkWin() != type && checkWin() != WHO_NONE)
		return -10;

	for (int i = 0; i < 9; i++)
	{
		if (m_grid[i] == WHO_NONE)	//still in game
			break;

		if (i == 8)
			return 0;
	}

	// If this maximizer's move 
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells 
		for (int i = 0; i < 9; ++i)
		{
			// Check if cell is empty 
			if (m_grid[i] == WHO_NONE)
			{
				// Make the move 
				m_grid[i] = type;

				// Call minimax recursively and choose 
				// the maximum value 
				best = max(best, minimax(type, !isMax));

				// Undo the move 
				m_grid[i] = WHO_NONE;
			}
		}
		return best;
	}

	// If this minimizer's move 
	else
	{
		int best = 1000;

		// Traverse all cells 
		for (int i = 0; i < 9; ++i)
		{
			// Check if cell is empty 
			if (m_grid[i] == WHO_NONE)
			{
				// Make the move 
				if (type == WHO_CIRCLE)
					m_grid[i] = WHO_CROSS;
				else
					m_grid[i] = WHO_CIRCLE;

				// Call minimax recursively and choose 
				// the minimum value 
				best = min(best, minimax(type, !isMax));

				// Undo the move 
				m_grid[i] = WHO_NONE;
			}
		}
		return best;
	}
}

SceneTicTacToev2::WHO_CONTENT SceneTicTacToev2::checkWin()
{
	for (int i = 0; i < 3; ++i) 
	{
		//Horizontal
		if (m_grid[i * 3] == m_grid[i * 3 + 1] && m_grid[i * 3] == m_grid[i * 3 + 2] && m_grid[i * 3] != WHO_NONE)
		{
			return m_grid[i * 3];
		}
		//Vertical
		else if (m_grid[i] == m_grid[i + 3] && m_grid[i] == m_grid[i + 6] && m_grid[i] != WHO_NONE)
		{
			return m_grid[i];
		}
	}

	//Diagonal >^
	if (m_grid[0] == m_grid[4] && m_grid[0] == m_grid[8])
	{
		if (m_grid[0] != WHO_NONE)
		{
			return m_grid[0];
		}
	}

	//Diagonal >v
	else if (m_grid[6] == m_grid[4] && m_grid[6] == m_grid[2])
	{
		if (m_grid[6] != WHO_NONE)
		{
			return m_grid[6];
		}
	}

	return WHO_NONE;
}

void SceneTicTacToev2::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_CROSS:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CROSS], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_CIRCLE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CIRCLE], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneTicTacToev2::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight * 0.5f, m_worldHeight * 0.5f, -1.f);
	modelStack.Scale(m_worldHeight, m_worldHeight, m_worldHeight);
	RenderMesh(meshList[GEO_TICTACTOE], false);
	modelStack.PopMatrix();

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	//On screen text
	static std::string winnerText[] = {"Draw", "Cross wins", "Circle wins"};

	std::ostringstream ss;
	ss.precision(3);
	ss << "Speed:" << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);

	ss.str("");
	ss << "Count:" << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 9);

	ss.str("");
	ss << "Turn:" << (m_bCrossTurn ? "Cross" : "Circle");
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 12);

	if (m_bGameOver)
	{
		ss.str("");
		ss << winnerText[static_cast<int>(m_winner)];	
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 15);
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Tic Tac Toe (R to reset)", Color(0, 1, 0), 3, 50, 0);
}

void SceneTicTacToev2::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if (m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}
