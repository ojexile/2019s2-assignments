#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
#include "LoadHmap.h"
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
	if (Application::IsKeyPressed('E'))
	{
		trans->Translate(m_fMovementSpeed / 10 * Vector3{ 0,1,0 });
	}
	if (Application::IsKeyPressed('Q'))
	{
		trans->Translate(-m_fMovementSpeed / 10 * Vector3{ 0,1,0 });
	}
	// Gun Position
	//m_Gun->GetComponent<TransformComponent>()->SetRelativePosition({ vCameraFront.x, vCameraFront.y+1.7f, vCameraFront .z});
	// Fire
	if (Application::IsMousePressed(0))
	{
		this->m_Gun->GetComponent<GunScript>()->PullTrigger(vCameraFront);
	}
	else
	{
		this->m_Gun->GetComponent<GunScript>()->ReleaseTrigger();
	}
	// Underwater
	if (trans->GetPosition().y < -5)
	{
		// Trigger underwater
		SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Underwater"));
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
	}
	// TODO Constrain to terrain
	Vector3 pos = trans->GetPosition();
	trans->SetPosition(pos.x, 100.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500) - 20, pos.z);
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}