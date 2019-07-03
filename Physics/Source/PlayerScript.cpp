#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
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
			Instantiate("CUBE");
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
}