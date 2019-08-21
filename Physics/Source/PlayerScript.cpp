#include "PlayerScript.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "CameraScript.h"
#include "GunScript.h"
#include "GrenadeScript.h"
#include "InventoryScript.h"
PlayerScript::PlayerScript(Behaviour* beh, GameObject* Reticle, GameObject* gun, GameObject* grenade)
	: EntityScript(beh)
{
	m_Reticle = Reticle;
	m_Gun = gun;
	m_Grenade = grenade;
}

PlayerScript::~PlayerScript()
{
}
void PlayerScript::Start()
{
	GetCameraGO()->GetComponent<CameraComponent>()->SetMouseUseFloatYaw(false);
}
void PlayerScript::SetCanJump(bool b)
{
	m_bCanJump = b;
}
bool PlayerScript::GetCanJump()
{
	return m_bCanJump;
}
void PlayerScript::Update(double dt)
{
	EntityScript::Update(dt);
	UpdateBehaviour();
	AudioManager::GetInstance()->UpdateListener(GetPosition(), GetCamera()->GetDir());
	AudioManager::GetInstance()->UpdateFading(dt);
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

	Rigidbody* rb = GetComponent<Rigidbody>();
	//// Movement
	//if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") > 0)
	//{
	//	//rb->AddForce(vPlayerFront  *m_fAccel);
	//	bMoved = true;
	//	Move(CameraScript::GetFront());
	//}
	//if (InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") < 0)
	//{
	//	//rb->AddForce(vPlayerFront  * -m_fAccel);
	//	bMoved = true;
	//	Move(-CameraScript::GetFront());
	//}
	//if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") < 0)
	//{
	//	//rb->AddForce(vRight  * -m_fAccel);
	//	bMoved = true;
	//	Move(-CameraScript::GetRight());
	//}
	//if (InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") > 0)
	//{
	//	//rb->AddForce(vRight  * m_fAccel);
	//	bMoved = true;
	//	Move(CameraScript::GetRight());
	//}
	//if (InputManager::GetInstance()->GetInputStrength("PlayerJump") != 0)
	//{
	//	//if (m_bCanJump)
	//	//{
	//	//	m_bCanJump = false;
	//	//	rb->AddForce({ 0,m_fJumpForce,0 });
	//	//	rb->SetVel(Vector3(rb->GetVel().x, 0, rb->GetVel().z));
	//	//	Notify("Jump");
	//	//}
	//}
	if (InputManager::GetInstance()->GetInputStrength("PlayerInteract") != 0)
	{
		Notify("Interact");
	}
	Vector3 vDir = m_Reticle->TRANS->GetPosition() - GetPosition();
	Vector3 vDir2 = m_Reticle->TRANS->GetPosition() - GetPosition();
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
	Vector3 vGunDir = m_Reticle->TRANS->GetPosition() - m_Gun->TRANS->GetPosition();
	if (!vGunDir.IsZero())
	{
		vGunDir.Normalize();
		m_Gun->TRANS->SetRelativeRotation(AngleBetween(vGunDir, vDir), 0, 1, 0);
	}
	if (InputManager::GetInstance()->GetInputStrength("Fire") != 0 && m_Reticle->IsActive())
	{
		m_Gun->GUN->PullTrigger(vGunDir, dt);
	}
	if (InputManager::GetInstance()->GetInputStrength("Fire") == 0 && m_Reticle->IsActive())
	{
		m_Gun->GUN->ReleaseTrigger();
	}

	if (InputManager::GetInstance()->GetInputStrength("Reload"))
		m_Gun->GUN->ReloadWeapon();

	if (InputManager::GetInstance()->GetInputStrength("Grenade") != 0)
	{
		m_Grenade->GetComponent<GrenadeScript>()->PullPin();
	}
	else if (InputManager::GetInstance()->GetInputStrength("Grenade") == 0)
	{
		m_Grenade->GetComponent<GrenadeScript>()->ThrowGrenade(vDir2, m_Grenade, (float)dt);
	}

	if (InputManager::GetInstance()->GetInputStrength("Mouse"))
	{
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
		m_Reticle->SetActive(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
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
	if (GetValues()->GetHealth() < 30)
	{
		AudioManager::GetInstance()->QueueFade(0, 0.3, "low_piano");
		AudioManager::GetInstance()->QueueFade(1, 0.3, "high_piano");
	}
	else
	{
		AudioManager::GetInstance()->QueueFade(1, 0.3, "low_piano");
		AudioManager::GetInstance()->QueueFade(0, 0.3, "high_piano");
	}
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
	RIGID->AddForce(vDir * 3000);
}