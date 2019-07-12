#include "PlayerScript.h"
#include "KeyboardManager.h"
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
	Vector3 vRight = m_vCameraFront->Cross(*m_vCameraUp);
	static bool triggered = false;
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
	{
		trans->Translate(fSpeed * *m_vCameraFront);
		if (!triggered)
		{
			Instantiate(m_GORef);
			triggered = true;
		}
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
	{
		trans->Translate(-fSpeed * *m_vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
	{
		trans->Translate(-fSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
	{
		trans->Translate(fSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveUp"))
	{
		trans->Translate(fSpeed * *m_vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
	{
		trans->Translate(-fSpeed * *m_vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("Susu"))
	{
		//AudioManager::GetInstance()->Play3D("susu.wav", Vector3(0, 0, 2));
	}
}