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

	static const float BALL_SPEED = 5.f;
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
				//if (random <= 0.25f)
				//{
				//	go->target += Vector3(m_gridSize, 0, 0);
				//}
				//else if (random <= 0.5f)
				//{
				//	go->target -= Vector3(m_gridSize, 0, 0);
				//}
				//else if (random <= 0.75f)
				//{
				//	go->target += Vector3(0, m_gridSize, 0);
				//}
				//else
				//{
				//	go->target -= Vector3(0, m_gridSize, 0);

				//}

				go->steps++;

				//Exercise: set boundaries so that game objects would not leave scene
				const float maxGridVal = m_worldHeight - m_gridOffset;

				go->target.x = Math::Clamp(go->target.x, m_gridOffset, maxGridVal);
				go->target.y = Math::Clamp(go->target.y, m_gridOffset, maxGridVal);				
				//Exercise: change the conditions so that the game objects can move randomly

				//Exercise: set some areas in the scene so that the game objects will go to different areas at various time of the day
				Vector3 area1(m_gridOffset, m_gridOffset, 0);
				Vector3 area2(m_gridOffset, maxGridVal, 0);
				Vector3 area3(maxGridVal, maxGridVal, 0);
				Vector3 area4(maxGridVal, m_gridOffset, 0);

				if (random <= 0.25f)
				{
					go->target = area1;
				}
				else if (random <= 0.5f)
				{
					go->target = area2;
				}
				else if (random <= 0.75f)
				{
					go->target = area3;
				}
				else
				{
					go->target = area4;
				}
			}
			else
			{
				// updown; up = true, down = false
				// leftright; left = true, right = false;
				// yvalid; if the game should consider y-movement
				// xvalid; if the game should consider x-movement
				bool updown, yvalid, leftright, xvalid;
				if (dir.x > Math::EPSILON && dir.x > 0.f)
				{
					leftright = true;
					xvalid = true;
				}
				else if (dir.x < Math::EPSILON && dir.x < 0.f)
				{
					leftright = false;
					xvalid = true;
				}
				else
				{
					xvalid = false;
				}

				if (dir.y > Math::EPSILON&& dir.y > 0.f)
				{
					updown = true;
					yvalid = true;
				}

				else if (dir.y < Math::EPSILON&& dir.y < 0.f)
				{
					updown = false;
					yvalid = true;
				}
				else
				{
					yvalid = false;
				}

				if (xvalid && yvalid)
				{

				}

				else
				{
					if (xvalid)
					{

					}
					else if (yvalid)
					{

					}
				}
				dir.Normalize();
				go->pos += dir * BALL_SPEED * static_cast<float>(dt) * m_speed;
			}
		}
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
