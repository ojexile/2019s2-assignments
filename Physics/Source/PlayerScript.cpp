#include "PlayerScript.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "InputManager.h"

PlayerScript::PlayerScript()
{
	m_CurrentState = nullptr;

	m_fJumpForce = 3000.f;
}

PlayerScript::~PlayerScript()
{
	if (m_CurrentState)
		delete m_CurrentState;
}
void PlayerScript::Start()
{
	GetCameraGO()->GetComponent<CameraComponent>()->SetMouseUseFloatYaw(false);
}
void PlayerScript::Update(double dt)
{
	AudioManager::GetInstance()->UpdateListener(GetPosition(), GetCamera()->GetDir());
	// TransformComponent* trans = GetComponent<TransformComponent>();
	// Movement================================================================================
	UpdateMovement(dt);
}

void PlayerScript::UpdateMovement(double dt)
{
	bool bMoved = false;
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
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

	Vector3 vPlayerFront = { -1,0,-1 };
	vPlayerFront.Normalize();
	Vector3 vRight = { 1,0,-1 };
	vRight.Normalize();

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
		rb->AddForce({ 0,m_fJumpForce,0 });
		jump = true;
	}
}