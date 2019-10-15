#include "SceneTicTacToe.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneTicTacToe::SceneTicTacToe()
{
}

SceneTicTacToe::~SceneTicTacToe()
{
}

void SceneTicTacToe::Init()
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

	m_bCrossTurn = false;
	m_bGameOver = false;
	m_winner = WHO_NONE;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < C_COUNT; j++)
		{
			m_wincondition[j][i] = 0;
		}
	}
}

GameObject* SceneTicTacToe::FetchGO()
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

//Exercise: This function should return 0 to 8, i.e. AI player's decision to put circle on one of the grids
int SceneTicTacToe::GetAIDecision()
{
	int self, other; // this is for double ai
	if (m_bCrossTurn)
	{
		self = WHO_CROSS -1;
		other = WHO_CIRCLE - 1;
	}
	else
	{
		other = WHO_CROSS - 1;
		self = WHO_CIRCLE - 1;
	}
	// ATTACK > PROTECT > RANDOM
	// prioritise attack (winning) over protecting (stopping other from winning over picking randomly
	
	// ATTACK: if any of the SELF's m_winconditions has a value of 2, find the remaining grid to take to win

	for (int i = 0; i < 8; i++)
	{
		if (m_wincondition[i][self] == 2)
		{
			switch (i)
			{
			case C036:
				if (m_grid[0] == WHO_NONE)
					return 0;
				if (m_grid[3] == WHO_NONE)
					return 3;
				if (m_grid[6] == WHO_NONE)
					return 6;
				break;
			case C147:
				if (m_grid[1] == WHO_NONE)
					return 1;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[7] == WHO_NONE)
					return 7;
				break;
			case C258:
				if (m_grid[2] == WHO_NONE)
					return 2;
				if (m_grid[5] == WHO_NONE)
					return 5;
				if (m_grid[8] == WHO_NONE)
					return 8;
				break;
			case C012:
				if (m_grid[0] == WHO_NONE)
					return 0;
				if (m_grid[1] == WHO_NONE)
					return 1;
				if (m_grid[2] == WHO_NONE)
					return 2;
				break;
			case C345:
				if (m_grid[3] == WHO_NONE)
					return 3;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[5] == WHO_NONE)
					return 5;
				break;
			case C678:
				if (m_grid[6] == WHO_NONE)
					return 6;
				if (m_grid[7] == WHO_NONE)
					return 7;
				if (m_grid[8] == WHO_NONE)
					return 8;
				break;
			case 246:
				if (m_grid[2] == WHO_NONE)
					return 2;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[6] == WHO_NONE)
					return 6;
				break;
			case C048:
				if (m_grid[0] == WHO_NONE)
					return 0;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[8] == WHO_NONE)
					return 8;
				break;
			}
		}
	}

	// PROTECT: if OTHER's m_wincondition is more than 2, intercept by finding the remaining grid to take.
	for (int i = 0; i < 8; i++)
	{
		if (m_wincondition[i][other] == 2)
		{
			switch (i)
			{
			case C036:
				if (m_grid[0] == WHO_NONE)
					return 0;
				if (m_grid[3] == WHO_NONE)
					return 3;
				if (m_grid[6] == WHO_NONE)
					return 6;
				break;
			case C147:
				if (m_grid[1] == WHO_NONE)
					return 1;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[7] == WHO_NONE)
					return 7;
				break;
			case C258:
				if (m_grid[2] == WHO_NONE)
					return 2;
				if (m_grid[5] == WHO_NONE)
					return 5;
				if (m_grid[8] == WHO_NONE)
					return 8;
				break;
			case C012:
				if (m_grid[0] == WHO_NONE)
					return 0;
				if (m_grid[1] == WHO_NONE)
					return 1;
				if (m_grid[2] == WHO_NONE)
					return 2;
				break;
			case C345:
				if (m_grid[3] == WHO_NONE)
					return 3;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[5] == WHO_NONE)
					return 5;
				break;
			case C678:
				if (m_grid[6] == WHO_NONE)
					return 6;
				if (m_grid[7] == WHO_NONE)
					return 7;
				if (m_grid[8] == WHO_NONE)
					return 8;
				break;
			case 246:
				if (m_grid[2] == WHO_NONE)
					return 2;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[6] == WHO_NONE)
					return 6;
				break;
			case C048:
				if (m_grid[0] == WHO_NONE)
					return 0;
				if (m_grid[4] == WHO_NONE)
					return 4;
				if (m_grid[8] == WHO_NONE)
					return 8;
				break;
			}
		}
	}

	// RANDOM: randomly picks a grid number that has a WHO_NONE on it.
	int random;
	do
	{
		random = Math::RandIntMinMax(0, 8);
	} while (m_grid[random] != WHO_NONE);

	return random;
}

void SceneTicTacToe::Update(double dt)
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
	}

	//Input Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
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

		if ((posX > 0.f && posX < m_worldHeight && posY > 0.f && posY < m_worldHeight)
			&& !m_bCrossTurn)
		{

			if (posX > 0.f && posX < m_worldHeight / 3) // bottom row
			{
				std::cout << "m_grid of 0-2\n";

				if (posY > 0.f && posY < m_worldHeight / 3) // bottom row
				{
					std::cout << "m_grid of 0\n";
					m_grid[0] = WHO_CIRCLE;
					m_wincondition[0][0]++;
					m_wincondition[4][0]++;
					m_wincondition[8][0]++;
				}
				if (posY > m_worldHeight / 3 && posY < 2 * m_worldHeight / 3) // mid
				{
					std::cout << "m_grid of 1\n";
					m_grid[1] = WHO_CIRCLE;
					m_wincondition[2][0]++;
					m_wincondition[4][0]++;

				}
				if (posY > 2 * m_worldHeight / 3 && posY < m_worldHeight) // top
				{
					std::cout << "m_grid of 2\n";
					m_grid[2] = WHO_CIRCLE;
					m_wincondition[1][0]++;
					m_wincondition[5][0]++;
					m_wincondition[7][0]++;

				}
			}
			if (posX > m_worldHeight / 3 && posX < 2 * m_worldHeight / 3) // mid
			{
				std::cout << "m_grid of 3-5\n";
				if (posY > 0.f && posY < m_worldHeight / 3) // bottom row
				{
					std::cout << "m_grid of 3\n";
					m_grid[3] = WHO_CIRCLE;
					m_wincondition[1][0]++;
					m_wincondition[5][0]++;

				}
				if (posY > m_worldHeight / 3 && posY < 2 * m_worldHeight / 3) // mid
				{
					std::cout << "m_grid of 4\n";
					m_grid[4] = WHO_CIRCLE;
					m_wincondition[2][0]++;
					m_wincondition[5][0]++;
					m_wincondition[8][0]++;

				}
				if (posY > 2 * m_worldHeight / 3 && posY < m_worldHeight) // top
				{
					std::cout << "m_grid of 5\n";
					m_grid[5] = WHO_CIRCLE;
					m_wincondition[3][0]++;
					m_wincondition[5][0]++;
				}
			}
			if (posX > 2 * m_worldHeight / 3 && posX < m_worldHeight) // top
			{
				std::cout << "m_grid of 6-8\n";
				if (posY > 0.f && posY < m_worldHeight / 3) // bottom row
				{
					std::cout << "m_grid of 6\n";
					m_grid[6] = WHO_CIRCLE;
					m_wincondition[1][0]++;
					m_wincondition[6][0]++;
					m_wincondition[7][0]++;
				}
				if (posY > m_worldHeight / 3 && posY < 2 * m_worldHeight / 3) // mid
				{
					std::cout << "m_grid of 7\n";
					m_grid[7] = WHO_CIRCLE;
					m_wincondition[2][0]++;
					m_wincondition[6][0]++;
				}
				if (posY > 2 * m_worldHeight / 3 && posY < m_worldHeight) // top
				{
					std::cout << "m_grid of 8\n";
					m_grid[8] = WHO_CIRCLE;
					m_wincondition[3][0]++;
					m_wincondition[6][0]++;
					m_wincondition[8][0]++;
				}
			}

			m_bCrossTurn = true;
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
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}

	if (m_bCrossTurn)
	{
		GetAIDecision();
		//Exercise: Call GetAIDecision() and put cross on grid
	}

	//Game Logic Section
	//Exercise: Check draw, cross wins or circle wins	// in GetAIDecision()
}


void SceneTicTacToe::RenderGO(GameObject *go)
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

void SceneTicTacToe::Render()
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

	// CODE TO RENDER CIRCLES AND CROSSES
	for (int i = 0; i < 9; i++)
	{
		modelStack.PushMatrix();

		if (i < 3)
		{
			modelStack.Translate(m_gridOffset, 0, 0);

			if (i == 0)
			{
				modelStack.Translate(0, m_gridOffset, 0);
			}
			if (i == 1)
			{
				modelStack.Translate(0, m_gridOffset + m_gridSize, 0);
			}
			if (i == 2)
			{
				modelStack.Translate(0, m_gridOffset + m_gridSize * 2, 0);
			}
		}
		else if (i < 6)
		{
			modelStack.Translate(m_gridOffset + m_gridSize, 0, 0);

			if (i - 3 == 0)
			{
				modelStack.Translate(0, m_gridOffset, 0);
			}
			if (i - 3 == 1)
			{
				modelStack.Translate(0, m_gridOffset + m_gridSize, 0);
			}
			if (i - 3 == 2)
			{
				modelStack.Translate(0, m_gridOffset + m_gridSize * 2, 0);
			}

		}
		else if (i < 9)
		{
			modelStack.Translate(m_gridOffset + m_gridSize * 2, 0, 0);
			if (i - 6 == 0)
			{
				modelStack.Translate(0, m_gridOffset, 0);
			}
			if (i - 6 == 1)
			{
				modelStack.Translate(0, m_gridOffset + m_gridSize, 0);
			}
			if (i - 6 == 2)
			{
				modelStack.Translate(0, m_gridOffset + m_gridSize * 2, 0);
			}
		}

		modelStack.Scale(m_gridSize * 0.5f, m_gridSize * 0.5f, m_gridSize * 0.5f);
		if (m_grid[i] == WHO_CIRCLE)
			RenderMesh(meshList[GEO_CIRCLE], false);
		else if (m_grid[i] == WHO_CROSS)
			RenderMesh(meshList[GEO_CROSS], false);
		modelStack.PopMatrix();
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

void SceneTicTacToe::Exit()
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
