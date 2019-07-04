#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
PlayerScript::PlayerScript()
{
}

PlayerScript::~PlayerScript()
{
}
void PlayerScript::Start()
{
}
void PlayerScript::Update(double dt)
{
	Vector3 vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	Vector3 vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fSpeed = 50 * (float)dt;
	Vector3 vRight = vCameraFront.Cross(vCameraUp);
	static bool triggered = false;
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
	{
		trans->Translate(fSpeed * vCameraUp);
		if (!triggered)
		{
			Instantiate("Cube");
			triggered = true;
		}
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
	{
		trans->Translate(-fSpeed * vCameraFront);
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
		trans->Translate(fSpeed * vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
	{
		trans->Translate(-fSpeed * vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("Susu"))
	{
		AudioManager::GetInstance()->Play3D("susu.wav", Vector3(0, 0, 2));
	}
}