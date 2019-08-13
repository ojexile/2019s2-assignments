#include "PlayerScript.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "InputManager.h"

#define MAX_HEALTH 100
PlayerScript::PlayerScript()
{
	m_CurrentState = nullptr;
	m_bFirstPerson = true;
	m_fJumpForce = 10000.f;
	m_fHealth = MAX_HEALTH;


}

PlayerScript::~PlayerScript()
{
	if (m_CurrentState)
		delete m_CurrentState;
}
void PlayerScript::Start()
{
	SwitchView();
}
void PlayerScript::Update(double dt)
{
	AudioManager::GetInstance()->UpdateListener(GetPosition(), GetCamera()->GetDir());
	// TransformComponent* trans = GetComponent<TransformComponent>();
	// Movement================================================================================
	UpdateMovement(dt);
}
void PlayerScript::SwitchView()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	if (m_bFirstPerson)
	{
		GetCameraGO()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
		GetCameraGO()->GetComponent<CameraComponent>()->SetMouseUseFloatYaw(false);

		GetCamera()->SetDir(Vector3{-1,-1,-1}.Normalize());


		m_bFirstPerson = false;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

		SetTopDownPos();

		m_bFirstPerson = true;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
	}
}
void PlayerScript::SetTopDownPos()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	GameObject* cam = GetCameraGO();
	//trans->SetPosition(0, 0, 0);
	cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, -90);
	Vector3 CamDir = GetCamera()->GetDir();
	Vector3 newRelPos = trans->GetPosition();
	newRelPos = -newRelPos;
	newRelPos.z += CamDir.z * -200;
	newRelPos.y = CamDir.y * -200;
	cam->GetComponent<TransformComponent>()->SetRelativePosition(newRelPos);
}
void PlayerScript::UpdateMovement(double dt)
{
	bool bMoved = false;
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();

	if (!m_bFirstPerson)
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

		Vector3 vCameraFront = GetCamera()->GetDir();
		Vector3 vCameraUp = GetCamera()->GetUp();

		Vector3 vPlayerFront = vCameraFront;
		vPlayerFront.y = 0;
		vPlayerFront.Normalize();

		Vector3 vRight = vCameraFront.Cross(vCameraUp);
		Rigidbody* rb = GetComponent<Rigidbody>();
		// Movement
		if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") > 0)
		{
			//rb->AddForce(vPlayerFront  *m_fAccel);
			//bMoved = true;
			Move(vPlayerFront);
		}
		if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") < 0)
		{
			//rb->AddForce(vPlayerFront  * -m_fAccel);
			//bMoved = true;
			Move(-vPlayerFront);
		}
		if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") < 0)
		{
			//rb->AddForce(vRight  * -m_fAccel);
			//bMoved = true;
			Move(-vRight);
		}
		if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") > 0)
		{
			//rb->AddForce(vRight  * m_fAccel);
			//bMoved = true;
			Move(vRight);
		}
		static bool jump = false;
		if (InputManager::GetInstance()->GetInputStrength("PlayerJump") == 0)
		{
			jump = false;
		}
		if (InputManager::GetInstance()->GetInputStrength("PlayerJump") != 0 && !jump)
		{
			rb->AddForce(vCameraUp  * m_fJumpForce);
			jump = true;
		}
		
	}
	// Camera================================================================================
	//if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
	//	SwitchView()
}