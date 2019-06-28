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
	m_vCameraTarget = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
}
void PlayerScript::Update(double dt)
{
	m_vCameraTarget = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 vDirFront = *m_vCameraTarget - trans->GetPosition();

	float fSpeed = 10 * (float)dt;
	Vector3 vRight = vDirFront.Cross(*m_vCameraUp);

	if (Application::IsKeyPressed('W'))
	{
		trans->translateObject(fSpeed * vDirFront);
	}
	if (Application::IsKeyPressed('S'))
	{
		trans->translateObject(-fSpeed * vDirFront);
	}
	if (Application::IsKeyPressed('A'))
	{
		trans->translateObject(-fSpeed * vRight);
	}
	if (Application::IsKeyPressed('D'))
	{
		trans->translateObject(fSpeed * vRight);
	}
	if (Application::IsKeyPressed('E'))
	{
		trans->translateObject(fSpeed * *m_vCameraUp);
	}
	if (Application::IsKeyPressed('Q'))
	{
		trans->translateObject(-fSpeed * *m_vCameraUp);
	}
}