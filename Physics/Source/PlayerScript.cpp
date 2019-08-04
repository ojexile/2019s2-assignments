#include "PlayerScript.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
PlayerScript::PlayerScript(GameObject* goRef)
	:m_GORef(goRef)
{
}

PlayerScript::~PlayerScript()
{
}
void PlayerScript::Start()
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
}
void PlayerScript::Update(double dt)
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fSpeed = 50 * (float)dt;
	Vector3 vRight = m_vCameraFront.Cross(m_vCameraUp);
	trans->Translate(Math::Clamp(InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack"),-10.f, 10.f) * m_vCameraFront);
	trans->Translate(Math::Clamp(InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft"), -10.f, 10.f) * vRight);
	SceneManager* SceneManager = SceneManager::GetInstance();
	Scene* CurrentScene = SceneManager->GetScene();
	Camera* Cam = CurrentScene->GetCamera();

	Cam->UpdateYawPitchMouse(InputManager::GetInstance()->GetInputStrength("PlayerLookLeftRight"), InputManager::GetInstance()->GetInputStrength("PlayerLookUpDown"));
	Cam->Update(dt);
	// TODO Constrain to terrain===============
	//=================================================================
	//Vector3 pos = trans->GetPosition();
	//trans->SetPosition(pos.x, 30.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500), pos.z);
}