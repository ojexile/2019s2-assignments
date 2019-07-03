#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
ChengPlayerScript::ChengPlayerScript(GameObject* gun)
	:m_Gun(gun)
{
	m_CurrentState = nullptr;
}

ChengPlayerScript::~ChengPlayerScript()
{
}
void ChengPlayerScript::Start()
{
}
void ChengPlayerScript::Update(double dt)
{
	if (!m_CurrentState)
	{
		m_CurrentState = new StandingState;
		m_CurrentState->OnEnter(this);
	}
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
		trans->Translate(m_fMovementSpeed* (float)dt * vPlayerFront);
	}
	if (Application::IsKeyPressed('S'))
	{
		trans->Translate(-m_fMovementSpeed * (float)dt * vPlayerFront);
	}
	if (Application::IsKeyPressed('A'))
	{
		trans->Translate(-m_fMovementSpeed * (float)dt* vRight);
	}
	if (Application::IsKeyPressed('D'))
	{
		trans->Translate(m_fMovementSpeed* (float)dt * vRight);
	}
	/*if (Application::IsKeyPressed('E'))
	{
		trans->Translate(fSpeed * *m_vCameraUp);
	}
	if (Application::IsKeyPressed('Q'))
	{
		trans->Translate(-fSpeed * *m_vCameraUp);
	}*/
	// Gun Position
	//m_Gun->GetComponent<TransformComponent>()->SetRelativePosition({ vCameraFront.x, vCameraFront.y+1.7f, vCameraFront .z});
	// Fire
	if (Application::IsKeyPressed(VK_SPACE))
	{
		this->m_Gun->GetComponent<GunScript>()->Shoot(vCameraFront);
	}
	// TODO Constrain to terrain
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}