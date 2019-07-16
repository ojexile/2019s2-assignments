#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
#include "LoadHmap.h"
#include "KeyboardManager.h"
ChengPlayerScript::ChengPlayerScript(GameObject* gun)
	:m_Gun(gun)
{
	m_CurrentState = nullptr;
	m_bState = false;
	m_fMovementSpeed = 1;
}

ChengPlayerScript::~ChengPlayerScript()
{
}
void ChengPlayerScript::Start()
{
}
void ChengPlayerScript::Update(double dt)
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
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 vPlayerFront = vCameraFront;
	vPlayerFront.y = 0;
	//vPlayerFront.Normalize();
	Vector3 vRight = vCameraFront.Cross(vCameraUp);

	// Movement
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
	{
		trans->Translate(m_fMovementSpeed * vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
	{
		trans->Translate(-m_fMovementSpeed * vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
	{
		trans->Translate(-m_fMovementSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
	{
		trans->Translate(m_fMovementSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveUp"))
	{
		trans->Translate(m_fMovementSpeed * vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
	{
		trans->Translate(-m_fMovementSpeed * vCameraUp);
	}
	// Gun Position
	// Fire

	if (Application::IsMousePressed(0))
	{
		this->m_Gun->GetComponent<GunScript>()->PullTrigger(vCameraFront);
	}
	else
	{
		this->m_Gun->GetComponent<GunScript>()->ReleaseTrigger();
	}
	// Underwater
	if (trans->GetPosition().y < -10)
	{
		// Trigger underwater
		SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Underwater"));
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
	}
	// TODO Constrain to terrain
	Vector3 pos = trans->GetPosition();
	//trans->SetPosition(pos.x, 50.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500) - 20, pos.z);
	trans->SetPosition({ pos.x,0,pos.z });

	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
	{
		if (m_bState)
		{
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(true);
			GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
			trans->SetPosition(0, 0, 0);
			cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 20, 0);
			cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(0, 0);
			m_bState = false;
		}
		else
		{
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
			GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
			trans->SetPosition(0, 0, 0);
			cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 300, 0);
			cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(0, -90);

			m_bState = true;
		}
	}
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}