#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
ChengPlayerScript::ChengPlayerScript()
{
	m_CurrentState = new StandingState;
}

ChengPlayerScript::~ChengPlayerScript()
{
}
void ChengPlayerScript::Start()
{
	m_CurrentState->OnEnter(this);
}
void ChengPlayerScript::Update(double dt)
{
	PlayerState* state = m_CurrentState->HandleInput(this, dt);
	if (m_CurrentState != state && state != nullptr)
	{
		state->OnEnter(this);
		delete m_CurrentState;
		m_CurrentState = state;
	}
	Vector3 vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	Vector3 vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 vPlayerFront = vCameraFront;
	vPlayerFront.y = 0;
	Vector3 vRight = vCameraFront.Cross(vCameraUp);
	// Movement
	if (Application::IsKeyPressed('W'))
	{
		trans->Translate(m_fMovementSpeed* dt * vPlayerFront);
	}
	if (Application::IsKeyPressed('S'))
	{
		trans->Translate(-m_fMovementSpeed * dt * vPlayerFront);
	}
	if (Application::IsKeyPressed('A'))
	{
		trans->Translate(-m_fMovementSpeed * dt* vRight);
	}
	if (Application::IsKeyPressed('D'))
	{
		trans->Translate(m_fMovementSpeed* dt * vRight);
	}
	/*if (Application::IsKeyPressed('E'))
	{
		trans->Translate(fSpeed * *m_vCameraUp);
	}
	if (Application::IsKeyPressed('Q'))
	{
		trans->Translate(-fSpeed * *m_vCameraUp);
	}*/

	// TODO Constrain to terrain
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}