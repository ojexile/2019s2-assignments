#include "RenderingManager.h"
#include "Application.h"
#include "RenderComponent.h"

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
void RenderingManager::RenderPassGPass(Scene* scene)
{
	m_renderPass = RENDER_PASS_PRE;
	m_lightDepthFBO.BindForWriting();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_gPassShaderID);
	//These matrices should change when light position or direction changes
	const float size = 250;
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
		m_lightDepthProj.SetToOrtho(-size, size, -size, size, -100, 100);
	else
		m_lightDepthProj.SetToPerspective(90, 1.f, 0.1, 20);

	m_lightDepthView.SetToLookAt(
		lights[0].position.x, lights[0].position.y, lights[0].position.z,
		0, 0, 0,
		0, 1, 0);
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

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
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
		projection.SetToPerspective(45, (float)Application::GetWindowWidth() / (float)Application::GetWindowHeight(), 0.1f, 1000);
		break;
	case CameraComponent::CAM_ORTHO:
	case CameraComponent::CAM_CUSTOM_ORTHO:
		projection.SetToOrtho(0, Application::GetWindowWidth(), 0, Application::GetWindowHeight(), -10, 10);
		break;
	default:
		DEFAULT_LOG("Camera type not unknown.");
		__debugbreak();
		break;
	}
	//projection.SetToOrtho(-100, 100, -100, 100, -100, 100);

	projectionStack.LoadMatrix(projection);
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		vCamPosition.x, vCamPosition.y, vCamPosition.z,
		Camera->m_vTarget.x, Camera->m_vTarget.y, Camera->m_vTarget.z,
		Camera->m_vUp.x, Camera->m_vUp.y, Camera->m_vUp.z
	);
	/*viewStack.LookAt(
			lights[0].position.x, lights[0].position.y, lights[0].position.z,
			0, 0, 0,
			0, 1, 0);*/
	std::stringstream ss;
	ss.precision(1);
	ss << Camera->m_vTarget.x << ", " << Camera->m_vTarget.y << ", " << Camera->m_vTarget.z;
	//CHENG_LOG("CAM TAR: ", ss.str());
	std::stringstream ss2;
	ss2.precision(1);
	ss2 << vCamPosition.x << ", " << vCamPosition.y << ", " << vCamPosition.z;
	//CHENG_LOG("CAM POS: ", ss2.str());
	ss.str("");
	ss << Camera->m_vDir.x << ", " << Camera->m_vDir.y << ", " << Camera->m_vDir.z;
	//CHENG_LOG("CAM DIR: ", ss.str());
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderWorld(scene);
}
void RenderingManager::RenderWorld(Scene* scene)
{
	GameObjectManager* GOM = scene->GetGameObjectManager();
	std::map<std::string, LayerData*>::iterator it;
	for (it = GOM->GetLayerList()->begin(); it != GOM->GetLayerList()->end(); it++)
	{
		// it->first == key
		// it->second == value
		// Switch shader
		if (it->first == "UI")
			continue;
		// m_programID = it->second->GetShader();
		// BindUniforms();
		std::vector<GameObject*> GOList = *it->second->GetGOList();
		for (unsigned i = 0; i < GOList.size(); ++i)
		{
			GameObject* go = GOList[i];
			if (!go->IsActive())
				continue;
			Vector3 vCamPos = scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
			RenderGameObject(go, vCamPos, false);
			for (unsigned i = 0; i < GOList[i]->GetChildList()->size(); ++i)
			{
				GameObject* goChild = GOList[i];
				if (!go->IsActive())
					continue;
				RenderGameObject(goChild, vCamPos, false);
			}
		}
	}
	// Render UI
	std::map<std::string, LayerData*>* map = GOM->GetLayerList();
	std::vector<GameObject*> GOList = *(*map)["UI"]->GetGOList();
	// m_programID = (*map)["UI"]->GetShader();
	// BindUniforms();
	for (unsigned i = 0; i < GOList.size(); ++i)
	{
		GameObject* go = GOList[i];
		if (!go->IsActive())
			continue;
		Vector3 vCamPos = scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
		RenderGameObject(go, vCamPos, true);
		for (unsigned i = 0; i < GOList[i]->GetChildList()->size(); ++i)
		{
			GameObject* goChild = GOList[i];
			if (!go->IsActive())
				continue;
			RenderGameObject(goChild, vCamPos, true);
		}
	}
}
void RenderingManager::RenderGameObject(GameObject* go, Vector3 vCamPos, bool bIsUI)
{
	RenderComponent* renderComponent = go->GetComponent<RenderComponent>(true);
	if (renderComponent == nullptr)
		return;
	Mesh* CurrentMesh = renderComponent->GetMesh();
	if (!CurrentMesh)
	{
		DEFAULT_LOG("Mesh not initialised");
		return;
	}
	modelStack.PushMatrix();
	TransformComponent* trans = go->GetComponent<TransformComponent>();
	Vector3 vGameObjectPosition = trans->GetPosition();
	Vector3 vGameObjectRotation = trans->GetRotation();
	float fGameObjectRotationDegrees = trans->GetDegrees();
	Vector3 vGameObjectScale = trans->GetScale();

	modelStack.Translate(vGameObjectPosition.x, vGameObjectPosition.y, vGameObjectPosition.z);
	modelStack.Scale(vGameObjectScale.x, vGameObjectScale.y, vGameObjectScale.z);

	if (renderComponent->IsBillboard())
	{
		float rAngle = atan2((vCamPos.x - trans->GetPosition().x), (vCamPos.z - trans->GetPosition().z));
		float dAngle = Math::RadianToDegree(rAngle);

		modelStack.Rotate(dAngle, 0.f, 1.f, 0.f);
	}
	if (fGameObjectRotationDegrees != 0)
		modelStack.Rotate(fGameObjectRotationDegrees, vGameObjectRotation.x, vGameObjectRotation.y, vGameObjectRotation.z);
	if (!bIsUI)
		RenderMesh(CurrentMesh, go->GetComponent<RenderComponent>()->GetLightEnabled());
	else
		RenderUI(CurrentMesh, go->GetComponent<RenderComponent>()->GetLightEnabled());

	modelStack.PopMatrix();
}
void RenderingManager::Exit()
{
	RenderingManagerBase::Exit();
	//Cleanup GameObjects
}