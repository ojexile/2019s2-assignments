#include "RenderingManager.h"

RenderingManager::RenderingManager()
{
}

RenderingManager::~RenderingManager()
{
}

void RenderingManager::Init()
{
	RenderingManagerBase::Init();
	m_worldHeight = 600.f;
	m_worldWidth = 800;

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
}

void RenderingManager::Update(double dt)
{
	RenderingManagerBase::Update(dt);
}

void RenderingManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculating aspect ratio
	// m_worldHeight = 100.f;
	// m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

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

	// TODO Render loops goes here
}

void RenderingManager::Exit()
{
	RenderingManagerBase::Exit();
	//Cleanup GameObjects
}