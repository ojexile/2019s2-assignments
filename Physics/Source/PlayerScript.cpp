#include "PlayerScript.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "KeyboardManager.h"

#define MAX_HEALTH 100
PlayerScript::PlayerScript()
{
	m_CurrentState = nullptr;
	m_bState = false;
	m_fMovementSpeed = 1;

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
	TransformComponent* trans = GetComponent<TransformComponent>();

	TransformComponent* CamTrans = GetCameraGO()->TRANS;
	CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -trans->GetPosition().z - 0);
	GetCamera()->SetDir(-90, -90);
}
void PlayerScript::Update(double dt)
{
	AudioManager::GetInstance()->UpdateListener(GetPosition(), GetCamera()->GetDir());
	TransformComponent* trans = GetComponent<TransformComponent>();
	// Movement================================================================================
	UpdateMovement(dt);
}
void PlayerScript::SetMovementSpeed(float f, float accel)
{
	m_fMovementSpeed = f;
	m_fAccel = accel;
}
void PlayerScript::SwitchView()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	if (m_bState)
	{
		GetCameraGO()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
		GetCameraGO()->GetComponent<CameraComponent>()->SetMouseEnabled(true);
		GameObject* cam = GetCameraGO();
		//trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 10, 0);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, 0);

		m_bState = false;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
		SetDefaultCamPos();

		m_bState = true;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
	}
}
void PlayerScript::SetDefaultCamPos()
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
void PlayerScript::UpdateMovement(double dt)
{
	bool bMoved = false;
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();

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
		vPlayerFront.Normalize();

		Vector3 vRight = vCameraFront.Cross(vCameraUp);
		Rigidbody* rb = GetComponent<Rigidbody>();
		// Movement
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
		{
			rb->IncrementForce(vPlayerFront  *m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
		{
			rb->IncrementForce(vPlayerFront  * -m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
		{
			rb->IncrementForce(vRight  * -m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
		{
			rb->IncrementForce(vRight  * m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("Jump"))
		{
			rb->IncrementForce(vCameraUp  * m_fJumpForce);
		}
		// Cap speed
		if (rb->GetVel().Length() > m_fMovementSpeed)
		{
			rb->SetVel(rb->GetVel().Normalize() * m_fMovementSpeed);
		}
		// bob
		if (bMoved)
		{
			const float maxBob = 0.3f;
			static float speed = 0.07f * m_fMovementSpeed;
			static float offset = 0;
			if (offset > maxBob)
				speed = -fabs(speed);
			if (offset < -maxBob)
				speed = fabs(speed);
			float off = speed * (float)dt;
			GetCameraGO()->GetComponent<TransformComponent>()->TranslateRelative(0, off, 0);
			offset += off;
		}
	}

	// Camera================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
		SwitchView();
}