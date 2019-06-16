#include "SceneAsteroid.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneAsteroid::SceneAsteroid()
{
}

SceneAsteroid::~SceneAsteroid()
{
}

void SceneAsteroid::Init()
{
	SceneBase::Init();

	//Physics code here
	m_speed = 1.f;
	
	Math::InitRNG();

	//Exercise 2a: Construct 100 GameObject with type GO_ASTEROID and add into m_goList

	//Exercise 2b: Initialize m_lives and m_score

	//Exercise 2c: Construct m_ship, set active, type, scale and pos
	m_ship = NULL;
}

GameObject* SceneAsteroid::FetchGO()
{
	//Exercise 3a: Fetch a game object from m_goList and return it
	return NULL;
}

void SceneAsteroid::Update(double dt)
{
	SceneBase::Update(dt);
	
	if(Application::IsKeyPressed('9'))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if(Application::IsKeyPressed('0'))
	{
		m_speed += 0.1f;
	}
	m_force.SetZero();
	//Exercise 6: set m_force values based on WASD
	if(Application::IsKeyPressed('W'))
	{
	}
	if(Application::IsKeyPressed('A'))
	{
	}
	if(Application::IsKeyPressed('S'))
	{
	}
	if(Application::IsKeyPressed('D'))
	{
	}
	//Exercise 8: use 2 keys to increase and decrease mass of ship

	//Exercise 11: use a key to spawn some asteroids

	//Exercise 14: use a key to spawn a bullet

	//Exercise 15: limit the spawn rate of bullets

	//Mouse Section
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

	//Physics Simulation Section

	//Exercise 7: Update ship's velocity based on m_force

	//Exercise 9: wrap ship position if it leaves screen

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			//Exercise 12: handle collision between GO_SHIP and GO_ASTEROID using simple distance-based check

			//Exercise 13: asteroids should wrap around the screen like the ship

			//Exercise 16: unspawn bullets when they leave screen

			//Exercise 18: collision check between GO_BULLET and GO_ASTEROID
		}
	}
}


void SceneAsteroid::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_SHIP:
		//Exercise 4a: render a sphere with radius 1

		//Exercise 17a: render a ship texture or 3D ship model
		//Exercise 17b:	re-orientate the ship with velocity
		break;
	case GameObject::GO_ASTEROID:
		//Exercise 4b: render a cube with length 2
		break;
	}
}

void SceneAsteroid::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

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

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	//On screen text

	//Exercise 5a: Render m_lives, m_score

	//Exercise 5b: Render position, velocity & mass of ship

	std::ostringstream ss2;
	ss2.precision(3);
	ss2 << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 6);
	
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Asteroid", Color(0, 1, 0), 3, 0, 0);
}

void SceneAsteroid::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ship)
	{
		delete m_ship;
		m_ship = NULL;
	}
}
