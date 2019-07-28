#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
#include "LoadHmap.h"
#include "KeyboardManager.h"
#include "MeshController.h"
#include "Mesh.h"
#include "Time.h"
#include "GauntletScript.h"
#include "Application.h"
#include "WorldValues.h"
#include "RojakScene2.h"
#include "SceneManager.h"
#include "RojakScene2.h"
#include "RojakAssignmentScene.h"

#define CAMERA_ANGLE_OFFSET 5
ChengPlayerScript::ChengPlayerScript(GameObject* gun, GameObject* cross, GameObject* gaunt)
	:m_Gun(gun)
	, m_CrossHair(cross)
	, m_Gaunt(gaunt)
{
	m_CurrentState = nullptr;
	m_bState = false;
	m_fMovementSpeed = 1;
	m_Light = SceneManager::GetInstance()->GetScene()->GetLightManager()->AddLight(Light::LIGHT_POINT);
	m_Light->power = 0;
	m_Light->color.r = 0;
	m_Light->color.g = 1;
}

ChengPlayerScript::~ChengPlayerScript()
{
	if (m_CurrentState)
		delete m_CurrentState;
}
void ChengPlayerScript::Start()
{
	SwitchView();
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 GDir = { 0,0,1 };
	GDir.Normalize();
	GDir *= 150;
	WorldValues::DefaultGravity = GDir;
	TransformComponent* CamTrans = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS;
	CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -trans->GetPosition().z - 0);
	SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -90);
}
void ChengPlayerScript::Update(double dt)
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	// Movement================================================================================
	UpdateMovement(dt);
	// Camera================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
		SwitchView();
	// Gauntlet================================================================================
	//if (KeyboardManager::GetInstance()->GetKeyTriggered("triggerGauntlet"))
	if (Application::IsMousePressed(1))
		m_Gaunt->GetComponent<RenderComponent>()->SetActive(true);
	else
		m_Gaunt->GetComponent<RenderComponent>()->SetActive(false);
	if (m_Gaunt->IsActive())
	{
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGauntForward"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->RotateForward();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGauntBackward"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->RotateBackward();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("useGauntlet"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->Use();
		}
	}
	if (m_bState)
	{
		// Tilt
		if (Application::IsKeyPressed(VK_LEFT))
		{
			Vector3 GDir = { 1,0,1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-110, -85);
		}
		else if (Application::IsKeyPressed(VK_RIGHT))
		{
			Vector3 GDir = { -1,0,1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-70, -85);
		}
		else if (Application::IsKeyPressed(VK_UP))
		{
			Vector3 GDir = { 0,0,-1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			TransformComponent* CamTrans = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS;
			CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -trans->GetPosition().z + 90);
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -60);
		}
		else if (Application::IsKeyPressed(VK_DOWN))
		{
			Vector3 GDir = { 0,0,1 };
			GDir.Normalize();
			GDir *= 150;
			WorldValues::DefaultGravity = GDir;
			TransformComponent* CamTrans = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS;
			CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -trans->GetPosition().z - 0);
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -90);
		}
		else
		{
			/*Vector3 GDir = { 0,0,1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			SetDefaultCamPos();
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -87);*/
		}
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("SwitchMap"))
	{
		SceneManager::GetInstance()->ChangeScene(new RojakAssignmentScene());
	}
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}
void ChengPlayerScript::SwitchView()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	if (m_bState)
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(true);
		GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
		//trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 10, 0);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, 0);
		m_Gun->SetActive(true);
		m_CrossHair->SetActive(true);
		m_bState = false;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
		SetDefaultCamPos();
		m_Gun->SetActive(false);
		m_CrossHair->SetActive(false);
		m_bState = true;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
	}
}
void ChengPlayerScript::SetDefaultCamPos()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
	//trans->SetPosition(0, 0, 0);
	cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, -90);
	Vector3 CamDir = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	Vector3 newRelPos = trans->GetPosition();
	newRelPos = -newRelPos;
	newRelPos.z += CamDir.z * -200;
	newRelPos.y = CamDir.y * -200;
	cam->GetComponent<TransformComponent>()->SetRelativePosition(newRelPos);
}
void ChengPlayerScript::UpdateMovement(double dt)
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	m_Light->position = { trans->GetPosition().x, trans->GetPosition().y, trans->GetPosition().z };
	m_Light->position.y += 100;
	if (!m_bState)
	{
		if (!m_CurrentState)
		{
			m_CurrentState = new StandingState;
			m_CurrentState->OnEnter(this);
		}
		PlayerState* state = m_CurrentState->HandleInput(this, dt);
		if (m_CurrentState != state && state != nullptr)
		{
			state->OnEnter(this);
			delete m_CurrentState;
			m_CurrentState = state;
		}

		Vector3 vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
		Vector3 vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();

		Vector3 vPlayerFront = vCameraFront;
		vPlayerFront.y = 0;
		//vPlayerFront.Normalize();
		Vector3 vRight = vCameraFront.Cross(vCameraUp);

		// Movement
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
		{
			trans->Translate(m_fMovementSpeed * vPlayerFront);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
		{
			trans->Translate(-m_fMovementSpeed * vPlayerFront);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
		{
			trans->Translate(-m_fMovementSpeed * vRight);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
		{
			trans->Translate(m_fMovementSpeed * vRight);
		}
		// Gun================================================================================
		// Fire--------------------------------------------------------------------------------
		if (Application::IsMousePressed(0))
		{
			this->m_Gun->GetComponent<GunScript>()->PullTrigger(vCameraFront, dt);
		}
		else
		{
			this->m_Gun->GetComponent<GunScript>()->ReleaseTrigger(vCameraFront);
		}
		//Reload--------------------------------------------------------------------------------
		if (KeyboardManager::GetInstance()->GetKeyTriggered("reload"))
		{
			m_Gun->GetComponent<GunScript>()->Reload();
		}
		// Underwater================================================================================
		if (trans->GetPosition().y < -10)
		{
			// Trigger underwater
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Underwater"));
		}
		else
		{
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
		}
	}
}