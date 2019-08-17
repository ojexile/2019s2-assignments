#include "PlayerScript.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "CameraScript.h"
#include "WeaponScript.h"
#include "GrenadeScript.h"
#include "InventoryScript.h"
PlayerScript::PlayerScript(GameObject* Reticle, GameObject* gun, GameObject* grenade)
	: m_Reticle(Reticle)
	, m_Gun(gun)
	, m_Grenade(grenade)
{
	m_CurrentState = nullptr;
	m_fJumpForce = 2000.f;
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
	
	m_Grenade->TRANS->SetPosition(GetPosition());

	// m_Gun->TRANS->SetPosition(GetPosition());
	// m_Gun->Update(dt);
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
	if (InputManager::GetInstance()->GetInputStrength("PlayerJump") != 0)
	{
		rb->AddForce({ 0,m_fJumpForce,0 });
		rb->SetVel(Vector3(rb->GetVel().x, 0, rb->GetVel().z));
		Notify("Jump");
	}
	if (InputManager::GetInstance()->GetInputStrength("PlayerInteract") != 0)
	{
		Notify("Interact");
	}
	Vector3 vDir = m_Reticle->TRANS->GetPosition() - GetPosition();
	if (!vDir.IsZero())
		vDir.Normalize();
	// Rotate to dir
	Vector3 PosDir = { 1,0,0 };
	float angle = AngleBetween(vDir, PosDir); // player defaults to look at pos x
	if (PosDir.Cross(vDir).y > 0)
	{
		GetTransform()->SetRotation(angle, 0, 1, 0);
	}
	else
	{
		GetTransform()->SetRotation(-angle, 0, 1, 0);
	}
	//
	if (InputManager::GetInstance()->GetInputStrength("Fire") != 0 && m_Reticle->IsActive())
	{
		m_Gun->GUN->PullTrigger(vDir, dt);
	}
	if (InputManager::GetInstance()->GetInputStrength("Fire") == 0 && m_Reticle->IsActive())
	{
		m_Gun->GUN->ReleaseTrigger();
	}

	if (InputManager::GetInstance()->GetInputStrength("Grenade") != 0)
	{
		m_Grenade->GetComponent<GrenadeScript>()->PullPin();
		
	}
	else if (InputManager::GetInstance()->GetInputStrength("Grenade") == 0)
	{
		m_Grenade->GetComponent<GrenadeScript>()->ThrowGrenade(vDir, m_Grenade, (float)dt);
	}

	if (InputManager::GetInstance()->GetInputStrength("Mouse"))
	{
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
		m_Reticle->SetActive(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
		m_Reticle->SetActive(true);
	}
	float fScroll = InputManager::GetInstance()->GetInputStrength("Zoom");
	if (fScroll != 0)
	{
		float fCamDist = std::stof(Preferences::GetPref(Resources::PreferencesTerm::CamDist));
		fCamDist += fScroll;
		fCamDist = Math::Clamp(fCamDist, 1.f, 100.f);
		Preferences::SetPref(Resources::PreferencesTerm::CamDist, std::to_string(fCamDist));
	}
	// CHENG_LOG("Player pos: ", vtos(GetPosition()));
}
void PlayerScript::Collide(GameObject* go)
{
	PartScript* ps = go->GetComponent<PartScript>(true);
	if (ps)
	{
		GetComponent<InventoryScript>()->AddItem(go);
		// CHENG_LOG("Part Taken");
	}
}
void PlayerScript::Dash()
{
	Vector3 vDir = m_Reticle->TRANS->GetPosition() - GetPosition();
	vDir.y = 0;
	if (!vDir.IsZero())
		vDir.Normalize();
	RIGID->AddForce(vDir * 2000);
}