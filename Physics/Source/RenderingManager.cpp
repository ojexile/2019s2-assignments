#include "RenderingManager.h"
#include "Application.h"
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
	//******************************* PRE RENDER PASS
	//*************************************
	RenderPassGPass(scene);
	//******************************* MAIN RENDER PASS
	//************************************
	RenderPassMain(scene);
}
void RenderingManager::RenderGameObject(GameObject* go)
{
	if (go->GetComponent<RenderComponent>(true) == nullptr)
		return;
	Mesh* CurrentMesh = go->GetComponent<RenderComponent>(true)->GetMesh();
	if (!CurrentMesh)
	{
		DEFAULT_LOG("Mesh not initialised");
		return;
	}
	modelStack.PushMatrix();
	Vector3 vGameObjectPosition = go->GetComponent<TransformComponent>()->GetPosition();
	Vector3 vGameObjectRotation = go->GetComponent<TransformComponent>()->GetRotation();
	float fGameObjectRotationDegrees = go->GetComponent<TransformComponent>()->GetDegrees();
	Vector3 vGameObjectScale = go->GetComponent<TransformComponent>()->GetScale();

	modelStack.Translate(vGameObjectPosition.x, vGameObjectPosition.y, vGameObjectPosition.z);
	modelStack.Scale(vGameObjectScale.x, vGameObjectScale.y, vGameObjectScale.z);
	if (fGameObjectRotationDegrees != 0)
		modelStack.Rotate(fGameObjectRotationDegrees, vGameObjectRotation.x, vGameObjectRotation.y, vGameObjectRotation.z);

	RenderMesh(CurrentMesh, go->GetComponent<RenderComponent>()->GetLightEnabled());
	modelStack.PopMatrix();
}
void RenderingManager::Exit()
{
	RenderingManagerBase::Exit();
	//Cleanup GameObjects
}

void RenderingManager::RenderPassGPass(Scene* scene)
{
	m_renderPass = RENDER_PASS_PRE;
		m_lightDepthFBO.BindForWriting();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_DEPTH_BUFFER_BIT);
		glUseProgram(m_gPassShaderID);
		//These matrices should change when light position or direction changes
		if (lights[0].type == Light::LIGHT_DIRECTIONAL)
			m_lightDepthProj.SetToOrtho(10, 10, 10, 10, 10, 20);
		else
			m_lightDepthProj.SetToPerspective(90, 1.f, 0.1, 20);
		m_lightDepthView.SetToLookAt(lights[0].position.x,
				lights[0].position.y+10, lights[0].position.z, 0, 0, 0, 0, 1, 0);
			RenderWorld(scene);
}
void RenderingManager::RenderPassMain(Scene* scene)
{
	m_renderPass = RENDER_PASS_MAIN;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Application::GetWindowWidth(),
		Application::GetWindowHeight());
		glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_programID);
		//pass light depth texture
		m_lightDepthFBO.BindForReading(GL_TEXTURE8);
		glUniform1i(m_parameters[U_SHADOW_MAP], 8);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameObject* CameraObject = scene->GetCameraGameObject();
		Vector3 vCamPosition = CameraObject->GetComponent<TransformComponent>()->GetPosition();
		if (!CameraObject)
			return;
		Camera* Camera = scene->GetCamera();
		// TODO proper target == pos handling
		if (vCamPosition == Camera->m_vTarget)
		{
			vCamPosition.z += 1;
		}

		//Calculating aspect ratio
		// m_worldHeight = 100.f;
		// m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		// Projection matrix
		Mtx44 projection;
		switch (CameraObject->GetComponent<CameraComponent>()->GetCameraType())
		{
		case CameraComponent::CAM_NONE:
			DEFAULT_LOG("Camera type not initialised.");
			__debugbreak();
			break;
		case CameraComponent::CAM_FIRST:
		case CameraComponent::CAM_CUSTOM_PERSPECT:
			projection.SetToPerspective(45, 16.f / 9.f, 1, 1000);
			break;
		case CameraComponent::CAM_ORTHO:
		case CameraComponent::CAM_CUSTOM_ORTHO:
			projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
			break;
		default:
			DEFAULT_LOG("Camera type not unknown.");
			__debugbreak();
			break;
		}

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
		CHENG_LOG("CAM TAR: ", ss.str());
		std::stringstream ss2;
		ss2.precision(1);
		ss2 << vCamPosition.x << ", " << vCamPosition.y << ", " << vCamPosition.z;
		CHENG_LOG("CAM POS: ", ss2.str());
		ss.str("");
		ss << Camera->m_vDir.x << ", " << Camera->m_vDir.y << ", " << Camera->m_vDir.z;
		CHENG_LOG("CAM DIR: ", ss.str());
		// Model matrix : an identity matrix (model will be at the origin)
		modelStack.LoadIdentity();

		RenderWorld(scene);
}
void RenderingManager::RenderWorld(Scene* scene)
{
	std::vector<GameObject*> GOList = *(scene->GetGameObjectManager()->GetGOList());
	for (unsigned i = 0; i < GOList.size(); ++i)
	{
		GameObject* go = GOList[i];
		if (!go->IsActive())
			continue;

		RenderGameObject(go);
		for (unsigned i = 0; i < GOList[i]->GetChildList()->size(); ++i)
		{
			GameObject* goChild = GOList[i];
			if (!go->IsActive())
				continue;
			RenderGameObject(goChild);
		}
	}
}