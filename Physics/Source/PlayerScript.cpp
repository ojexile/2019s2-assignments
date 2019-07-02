#include "PlayerScript.h"
#include "Application.h"
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
	if (Application::IsKeyPressed('W'))
	{
		trans->Translate(fSpeed * vCameraUp);
		if (!triggered)
		{
			Instantiate("CUBE");
			triggered = true;
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		trans->Translate(-fSpeed * vCameraFront);
	}
	if (Application::IsKeyPressed('A'))
	{
		trans->Translate(-fSpeed * vRight);
	}
	if (Application::IsKeyPressed('D'))
	{
		trans->Translate(fSpeed * vRight);
	}
	if (Application::IsKeyPressed('E'))
	{
		trans->Translate(fSpeed * vCameraUp);
	}
	if (Application::IsKeyPressed('Q'))
	{
		trans->Translate(-fSpeed * vCameraUp);
	}
}