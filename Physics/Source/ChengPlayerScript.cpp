#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
#include "LoadHmap.h"
#include "KeyboardManager.h"
#include "MeshController.h"
#include "Mesh.h"
#include "Time.h"
ChengPlayerScript::ChengPlayerScript(GameObject* gun, GameObject* cross, GameObject* gaunt, GameObject* repel)
	:m_Gun(gun)
	, m_CrossHair(cross)
	, m_Gaunt(gaunt)
	, m_Repel(repel)
{
	m_CurrentState = nullptr;
	m_bState = false;
	m_fMovementSpeed = 1;
	m_bGaunt = false;
	m_eStone = NONE;
	m_fRepelDuration = 0.3f;
}

ChengPlayerScript::~ChengPlayerScript()
{
	if (m_CurrentState)
		delete m_CurrentState;
}
void ChengPlayerScript::Start()
{
}
void ChengPlayerScript::Update(double dt)
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	if (!m_bState)
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

		Vector3 vPlayerFront = vCameraFront;
		vPlayerFront.y = 0;
		//vPlayerFront.Normalize();
		Vector3 vRight = vCameraFront.Cross(vCameraUp);

		// Movement
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
		{
			trans->Translate(m_fMovementSpeed * vPlayerFront);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
		{
			trans->Translate(-m_fMovementSpeed * vPlayerFront);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
		{
			trans->Translate(-m_fMovementSpeed * vRight);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
		{
			trans->Translate(m_fMovementSpeed * vRight);
		}
		//if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveUp"))
		//{
		//	trans->Translate(m_fMovementSpeed * vCameraUp);
		//}
		//if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
		//{
		//	trans->Translate(-m_fMovementSpeed * vCameraUp);
		//}
		// Gun================================================================================
		// Fire--------------------------------------------------------------------------------
		if (Application::IsMousePressed(0))
		{
			this->m_Gun->GetComponent<GunScript>()->PullTrigger(vCameraFront, dt);
		}
		else
		{
			this->m_Gun->GetComponent<GunScript>()->ReleaseTrigger(vCameraFront);
		}
		//Reload--------------------------------------------------------------------------------
		if (KeyboardManager::GetInstance()->GetKeyTriggered("reload"))
		{
			m_Gun->GetComponent<GunScript>()->Reload();
		}
		// Underwater================================================================================
		if (trans->GetPosition().y < -10)
		{
			// Trigger underwater
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Underwater"));
		}
		else
		{
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
		}
	}
	// Camera================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
	{
		if (m_bState)
		{
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(true);
			GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
			//trans->SetPosition(0, 0, 0);
			cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 20, 0);
			cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(0, 0);
			m_Gun->SetActive(true);
			m_CrossHair->SetActive(true);
			m_bState = false;
		}
		else
		{
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
			SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
			GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
			//trans->SetPosition(0, 0, 0);
			cam->GetComponent<TransformComponent>()->SetRelativePosition(-pos.x, 300, -pos.z);
			cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, -90);
			m_Gun->SetActive(false);
			m_CrossHair->SetActive(false);
			m_bState = true;
		}
	}
	// Gauntlet================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("triggerGauntlet"))
	{
		if (m_bGaunt)
		{
			m_Gaunt->SetActive(false);
			m_bGaunt = false;
		}
		else
		{
			m_Gaunt->SetActive(true);
			m_bGaunt = true;
		}
	}
	if (m_bGaunt)
	{
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGaunt"))
		{
			MeshController<Mesh>* mc = m_Gaunt->GetComponent<MeshController<Mesh>>();

			switch (m_eStone)
			{
			case ChengPlayerScript::NONE:
				mc->SetMesh("GauntSoul");
				break;
			case ChengPlayerScript::SOUL:
				mc->SetMesh("GauntReality");
				break;
			case ChengPlayerScript::REALITY:
				mc->SetMesh("GauntSpace");
				break;
			case ChengPlayerScript::SPACE:
				mc->SetMesh("GauntPower");
				break;
			case ChengPlayerScript::POWER:
				mc->SetMesh("GauntTime");
				break;
			case ChengPlayerScript::TIME:
				mc->SetMesh("GauntMind");
				break;
			case ChengPlayerScript::MIND:
				mc->SetMesh("Gaunt");
				break;
			default:
				break;
			}
			m_eStone = static_cast<eSTONES>((m_eStone + 1) % TOTAL);
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("useGauntlet"))
		{
			switch (m_eStone)
			{
			case ChengPlayerScript::NONE:
				break;
			case ChengPlayerScript::SOUL:

				break;
			case ChengPlayerScript::REALITY:

				break;
			case ChengPlayerScript::SPACE:

				break;
			case ChengPlayerScript::POWER:
			{
				m_Repel->SetActive(true);
				m_fStartRepel = Time::GetInstance()->GetElapsedTimeF();
			}
			break;
			case ChengPlayerScript::TIME:
				break;
			case ChengPlayerScript::MIND:

				break;
			default:
				break;
			}
			m_Gaunt->SetActive(false);
			m_bGaunt = false;
		}
	}
	if (m_Repel->IsActive())
	{
		if (Time::GetInstance()->GetElapsedTimeF() >= m_fStartRepel + m_fRepelDuration)
		{
			m_Repel->SetActive(false);
		}
	}
	// TODO Constrain to terrain================================================================================
	//trans->SetPosition(pos.x, 50.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500) - 20, pos.z);
	//trans->SetPosition({ pos.x,0,pos.z });
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}