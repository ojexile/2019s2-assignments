#include "SceneReversi.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneReversi::SceneReversi()
{
}

SceneReversi::~SceneReversi()
{
}

void SceneReversi::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_noGrid = 8;
	m_gridSize = m_worldHeight / 8;
	m_gridOffset = m_gridSize / 2;

	Reset();
}

void SceneReversi::Reset()
{
	//Exercise: Implement reset
}

void SceneReversi::Update(double dt)
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
		Reset();
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
		if (posX > 0 && posX < m_noGrid * m_gridSize && posY > 0 && posY < m_noGrid * m_gridSize)
		{
			int gridX = static_cast<int>(posX / m_gridSize);
			int gridY = static_cast<int>(posY / m_gridSize);
			int index = gridY * m_noGrid + gridX;
			//Exercise: Game Control
			if (!m_bGameOver)
			{
				if (m_grid[index] == WHO_NONE)
				{
					if (m_bBlackTurn)
					{
						//Exercise: Check if valid move
					}
					else //Exercise: For AI to take over
					{
					}
					//Game Logic Section - call methods
					//Exercise: Flips the existing disks on board
					//Exercise: Check if there is valid move for current color, if not forfeit the turn 
					//Exercise: Check draw, black wins or white wins
				}
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
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}

	if (!m_bGameOver)
	{
		//Exercise: For AI to take over white player (or both players)
	}
}

void SceneReversi::Render()
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

	//Exercise: Render Game board
	//Exercise: Render black and white seeds without GameObject

	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "Speed:" << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);

	//Exercise: Render number of black and white seeds
	//Exercise: Render whose turn (black or white)
	//Exercise: [When gameover] Render black wins, white wins or game draw
	ss.str("");
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 9);

	RenderTextOnScreen(meshList[GEO_TEXT], "Reversi (R to reset)", Color(0, 1, 0), 3, 50, 0);
}

void SceneReversi::Exit()
{
	SceneBase::Exit();
}
