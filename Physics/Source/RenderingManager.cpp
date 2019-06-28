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
	m_worldHeight = 100.f;
	m_worldWidth = 100.f;

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	SceneManager* SceneManager = SceneManager::GetInstance();
	Scene* CurrentScene = SceneManager->GetScene();
	Camera* Cam = CurrentScene->GetCamera();

	Cam->UpdateYawPitchMouse((float)xpos, (float)ypos);
}
void RenderingManager::SetMouseCallback(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, mouse_callback);
}

void RenderingManager::Update(double dt)
{
	RenderingManagerBase::Update(dt);
}

void RenderingManager::Render(Scene* scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GameObject* CameraObject = scene->GetCameraGameObject();
	Vector3 vCamPosition = CameraObject->GetComponent<TransformComponent>()->GetPosition();
	if (!CameraObject)
		return;
	Vector3 vCamPosition = CameraObject->GetTransform()->GetPosition();
	Camera* Camera = scene->GetCamera();
	// TODO proper target == pos handling
	if (vCamPosition == Camera->m_vTarget)
	{
		vCamPosition.z += 1;
	}

	//Calculating aspect ratio
	// m_worldHeight = 100.f;
	// m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	//projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projection.SetToPerspective(45, 16.f / 9.f, 1, 100);
	projectionStack.LoadMatrix(projection);
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		vCamPosition.x, vCamPosition.y, vCamPosition.z,
		Camera->m_vTarget.x, Camera->m_vTarget.y, Camera->m_vTarget.z,
		Camera->m_vUp.x, Camera->m_vUp.y, Camera->m_vUp.z
	);
	std::stringstream ss;
	ss.precision(1);
	ss << Camera->m_vTarget.x << ", " << Camera->m_vTarget.y << ", " << Camera->m_vTarget.z;
	std::string target = ss.str();
	DEFAULT_LOG("TARGET: ", ss.str());
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	// Render loops goes here
	std::vector<GameObject*> GOList = *scene->GetGameObjectManager().GetGOList();
	for (unsigned i = 0; i < GOList.size(); ++i)
	{
		GameObject* go = (GOList)[i];
		if (!go->IsActive())
			continue;
		if (go->GetComponent<RenderComponent>() == nullptr)
			continue;
		Mesh* CurrentMesh = go->GetComponent<RenderComponent>(true)->GetMesh();
		if (!CurrentMesh)
		{
			continue;
		}
		modelStack.PushMatrix();

		Vector3 vGameObjectPosition = go->GetComponent<TransformComponent>()->GetPosition();
		Vector3 vGameObjectRotation = go->GetComponent<TransformComponent>()->GetRotation();
		float fGameObjectRotationDegrees = go->GetComponent<TransformComponent>()->GetDegrees();
		Vector3 vGameObjectScale = go->GetComponent<TransformComponent>()->GetScale();

		// TODO Rotations
		modelStack.Translate(vGameObjectPosition.x, vGameObjectPosition.y, vGameObjectPosition.z);
		modelStack.Scale(vGameObjectScale.x, vGameObjectScale.y, vGameObjectScale.z);
		modelStack.Rotate(fGameObjectRotationDegrees, vGameObjectRotation.x, vGameObjectRotation.y, vGameObjectRotation.z);

		RenderMesh(CurrentMesh, go->GetComponent<RenderComponent>()->GetLightEnabled());

		modelStack.PopMatrix();
	}
}
void RenderingManager::Exit()
{
	RenderingManagerBase::Exit();
	//Cleanup GameObjects
}