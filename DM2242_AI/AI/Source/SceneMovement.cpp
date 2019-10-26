#include "SceneMovement.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneMovement::SceneMovement()
{
}

SceneMovement::~SceneMovement()
{
}

void SceneMovement::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;
	
	Math::InitRNG();

	m_objectCount = 0;
	m_noGrid = 20;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2;
	m_hourOfTheDay = 0;
}

GameObject* SceneMovement::FetchGO()
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
		GameObject *go = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(go);
	}
	return FetchGO();
}

void SceneMovement::Update(double dt)
{
	SceneBase::Update(dt);

	static const float BALL_SPEED = 20.f;
	static const float HOUR_SPEED = 1.f;

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	
	if(Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if(Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}

	m_hourOfTheDay += HOUR_SPEED * static_cast<float>(dt) * m_speed;
	if (m_hourOfTheDay >= 24.f)
		m_hourOfTheDay = 0;

	//Input Section
	static bool bLButtonState = false;
	if(!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if(bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if(!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if(bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
	static bool bSpaceState = false;
	if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = true;
		GameObject *go = FetchGO();
		go->id = m_objectCount;
		go->scale.Set(m_gridSize * 0.5f, m_gridSize * 0.5f, m_gridSize * 0.5f);
		go->pos.Set(m_gridOffset + 0 * m_gridSize, m_gridOffset + 0 * m_gridSize, 0);
		go->target = go->pos;
		go->steps = 0;
		go->targetLocation.Set(m_gridOffset + 0 * m_gridSize, m_gridOffset + 0 * m_gridSize, 0);
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}

	//Movement Section

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			if (go->steps > 100)
				continue;
			Vector3 dir = go->target - go->pos;
			if (dir.Length() < BALL_SPEED * dt * m_speed)
			{
				//GO->pos reach target
				go->pos = go->target;
				float random = Math::RandFloatMinMax(0.f, 1.f);
				//Exercise: use probability to decide go up or right
				/*if (random < 0.25f)
				{
					go->target.Set(go->pos.x, go->pos.y + m_gridSize, 0);
					go->steps++;
				}
				else if (random < 0.5f)
				{
					go->target.Set(go->pos.x + m_gridSize, go->pos.y, 0);
					go->steps++;
				}
				else if (random < 0.75f)
				{
					go->target.Set(go->pos.x, go->pos.y - m_gridSize, 0);
					go->steps++;
				}
				else
				{
					go->target.Set(go->pos.x - m_gridSize, go->pos.y, 0);
					go->steps++;
				}*/
				if (go->pos.x != go->targetLocation.x)
				{
					go->target.Set(go->targetLocation.x, go->pos.y, 0);
				}
				if (go->pos.y != go->targetLocation.y && go->pos.x == go->targetLocation.x)
				{
					go->target.Set(go->pos.x, go->targetLocation.y, 0);
				}
				//Exercise: set boundaries so that game objects would not leave scene
				if (go->target.x > m_gridSize * m_noGrid)
				{
					go->target.x = m_gridSize * m_noGrid - m_gridOffset;
				}
				else if (go->target.x < m_gridOffset)
				{
					go->target.x = m_gridOffset;
				}
				if (go->target.y > m_worldHeight)
				{
					go->target.y = m_worldHeight - m_gridOffset;
				}
				else if (go->target.y < m_gridOffset)
				{
					go->target.y = m_gridOffset;
				}
				//Exercise: change the conditions so that the game objects can move randomly

				//Exercise: set some areas in the scene so that the game objects will go to different areas at various time of the day
				if (m_hourOfTheDay >= 10 && m_hourOfTheDay < 11)
				{
					MoveAI();
				}
			}
			else
			{
				dir.Normalize();
				go->pos += dir * BALL_SPEED * static_cast<float>(dt) * m_speed;
			}
		}
	}
}

void SceneMovement::MoveAI()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		int randomX;
		int randomY;
		int randomTargetLocation = Math::RandIntMinMax(1, 5);
		switch (randomTargetLocation)
		{
		//blue area
		case 1:			
			randomX = Math::RandIntMinMax(1, 4);
			randomY = Math::RandIntMinMax(16, 18);
			break;
		//green area
		case 2:
			randomX = Math::RandIntMinMax(4, 6);
			randomY = Math::RandIntMinMax(4, 6);
			break;
		//purple area
		case 3:
			randomX = Math::RandIntMinMax(9, 12);
			randomY = Math::RandIntMinMax(9, 12);
			break;
		//red area
		case 4:
			randomX = Math::RandIntMinMax(15, 17);
			randomY = Math::RandIntMinMax(13, 16);
			break;
		//yellow area
		case 5:
			randomX = Math::RandIntMinMax(14, 15);
			randomY = Math::RandIntMinMax(2, 5);
			break;
		}
		go->targetLocation.Set(randomX * m_gridSize + m_gridOffset, randomY * m_gridSize + m_gridOffset, 0);
	}
}

void SceneMovement::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);

		std::ostringstream ss;
		ss << go->id;
		RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0));
		modelStack.PopMatrix();
		break;
	}
}

void SceneMovement::Render()
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
	RenderMesh(meshList[GEO_BG], false);
	modelStack.PopMatrix();

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	//On screen text

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
	ss.precision(4);
	ss << "Hour:" << m_hourOfTheDay;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 12);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Movement", Color(0, 1, 0), 3, 50, 0);
}

void SceneMovement::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}
