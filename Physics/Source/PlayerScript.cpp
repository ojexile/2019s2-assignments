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
		trans->Translate(fSpeed * vDirFront);
	}
	if (Application::IsKeyPressed('S'))
	{
		trans->Translate(-fSpeed * vDirFront);
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
		trans->Translate(fSpeed * *m_vCameraUp);
	}
	if (Application::IsKeyPressed('Q'))
	{
		trans->Translate(-fSpeed * *m_vCameraUp);
	}
}