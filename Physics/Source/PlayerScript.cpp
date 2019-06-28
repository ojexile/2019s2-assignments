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
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
}
void PlayerScript::Update(double dt)
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fSpeed = 5 * (float)dt;
	Vector3 vRight = m_vCameraFront->Cross(*m_vCameraUp);

	if (Application::IsKeyPressed('W'))
	{
		trans->Translate(fSpeed * *m_vCameraFront);
	}
	if (Application::IsKeyPressed('S'))
	{
		trans->Translate(-fSpeed * *m_vCameraFront);
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