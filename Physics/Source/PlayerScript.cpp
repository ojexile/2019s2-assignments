#include "PlayerScript.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "CameraScript.h"
#include "WeaponScript.h"

PlayerScript::PlayerScript(GameObject* Reticle, GameObject* gun)
	: m_Reticle(Reticle)
	, m_Gun(gun)
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
	EntityScript::Update(dt);
	AudioManager::GetInstance()->UpdateListener(GetPosition(), GetCamera()->GetDir());
	// Movement================================================================================
	UpdateMovement(dt);
	m_Gun->TRANS->SetPosition(GetPosition());
	m_Gun->Update(dt);
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

	Rigidbody* rb = GetComponent<Rigidbody>();
	// Movement
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") > 0)
	{
		//rb->AddForce(vPlayerFront  *m_fAccel);
		//bMoved = true;
		Move(CameraScript::GetFront());
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") < 0)
	{
		//rb->AddForce(vPlayerFront  * -m_fAccel);
		//bMoved = true;
		Move(-CameraScript::GetFront());
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") < 0)
	{
		//rb->AddForce(vRight  * -m_fAccel);
		//bMoved = true;
		Move(-CameraScript::GetRight());
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") > 0)
	{
		//rb->AddForce(vRight  * m_fAccel);
		//bMoved = true;
		Move(CameraScript::GetRight());
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
	Vector3 vDir = m_Reticle->TRANS->GetPosition() - GetPosition();
	if(!vDir.IsZero())
		vDir.Normalize();
	if (InputManager::GetInstance()->GetInputStrength("Fire") != 0 )
	{
		m_Gun->GetComponent<WeaponScript>()->PullTrigger(vDir, dt);
	}
	if (InputManager::GetInstance()->GetInputStrength("Fire") == 0 )
	{
		m_Gun->GetComponent<WeaponScript>()->ReleaseTrigger();
	}
	if (InputManager::GetInstance()->GetInputStrength("Mouse"))
	{
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
		m_Reticle->SetActive(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
		m_Reticle->SetActive(true);
		m_Reticle->TRANS->SetPosition(GetPosition());
	}
}
void PlayerScript::Collide(GameObject* go)
{
	PartScript* ps = go->GetComponent<PartScript>();
}