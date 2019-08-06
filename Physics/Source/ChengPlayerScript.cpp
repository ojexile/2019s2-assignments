#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
#include "LoadHmap.h"
#include "KeyboardManager.h"
#include "MeshController.h"
#include "Mesh.h"
#include "Time.h"
#include "GauntletScript.h"
#include "Application.h"
#include "WorldValues.h"
#include "RojakScene2.h"
#include "SceneManager.h"
#include "RojakScene2.h"
#include "RojakAssignmentScene.h"
#include "DataContainer.h"
#include "Constrain.h"
#include "AudioManager.h"

#define CAMERA_ANGLE_OFFSET 5
ChengPlayerScript::ChengPlayerScript(GameObject* gun, GameObject* cross, GameObject* gaunt)
	: m_CrossHair(cross)
	, m_Gaunt(gaunt)
{
	m_Guns.push_back(gun);
	m_CurrentGun = gun;
	m_CurrentGun->RENDER->SetBillboard(true);
	m_CurrentGun->GetComponent<GunScript>()->SetHolding(true);
	m_CurrentState = nullptr;
	m_bState = false;
	m_fMovementSpeed = 1;
	m_Light = SceneManager::GetInstance()->GetScene()->GetLightManager()->AddLight(Light::LIGHT_POINT);
	m_Light->power = 0;
	m_Light->color.r = 0;
	m_Light->color.g = 1;
	m_fJumpForce = 10000.f;
}

ChengPlayerScript::~ChengPlayerScript()
{
	if (m_CurrentState)
		delete m_CurrentState;
}
void ChengPlayerScript::Start()
{
	//m_Guns.at(0)->TRANS->SetPosition(SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->GetPosition());
	SwitchView();
	TransformComponent* trans = GetComponent<TransformComponent>();
	//Vector3 GDir = { 0,0,1 };
	//GDir.Normalize();
	//GDir *= 150;
	//WorldValues::DefaultGravity = GDir;
	TransformComponent* CamTrans = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS;
	CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -trans->GetPosition().z - 0);
	SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -90);
}
void ChengPlayerScript::Update(double dt)
{
	AudioManager::GetInstance()->UpdateListener(GetPosition(), GetCamera()->GetDir());
	TransformComponent* trans = GetComponent<TransformComponent>();
	// Movement================================================================================
	float bMoved = UpdateMovement(dt);
	UpdateGauntlet();
	UpdateTilt();
	UpdateConstrain();
}
void ChengPlayerScript::SetMovementSpeed(float f, float accel)
{
	m_fMovementSpeed = f;
	m_fAccel = accel;
}
void ChengPlayerScript::SwitchView()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	if (m_bState)
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(true);
		GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
		//trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 10, 0);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, 0);
		m_CurrentGun->SetActive(true);
		m_CrossHair->SetActive(true);
		m_bState = false;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
		SetDefaultCamPos();
		m_CurrentGun->SetActive(false);
		m_CrossHair->SetActive(false);
		m_bState = true;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
	}
}
void ChengPlayerScript::SetDefaultCamPos()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
	//trans->SetPosition(0, 0, 0);
	cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, -90);
	Vector3 CamDir = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	Vector3 newRelPos = trans->GetPosition();
	newRelPos = -newRelPos;
	newRelPos.z += CamDir.z * -200;
	newRelPos.y = CamDir.y * -200;
	cam->GetComponent<TransformComponent>()->SetRelativePosition(newRelPos);
}
bool ChengPlayerScript::UpdateMovement(double dt)
{
	bool bMoved = false;
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	m_Light->position = { trans->GetPosition().x, trans->GetPosition().y, trans->GetPosition().z };
	m_Light->position.y += 100;
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
		vPlayerFront.Normalize();
		//vPlayerFront.Normalize();
		Vector3 vRight = vCameraFront.Cross(vCameraUp);
		ChengRigidbody* rb = GetComponent<ChengRigidbody>();
		// Movement
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
		{
			// trans->Translate(m_fMovementSpeed * vPlayerFront);
			rb->IncrementForce(vPlayerFront  *m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
		{
			rb->IncrementForce(vPlayerFront  * -m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
		{
			// trans->Translate(-m_fMovementSpeed * vRight);
			rb->IncrementForce(vRight  * -m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
		{
			// trans->Translate(m_fMovementSpeed * vRight);
			rb->IncrementForce(vRight  * m_fAccel);
			bMoved = true;
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("Jump"))
		{
			// trans->Translate(m_fMovementSpeed * vRight);
			rb->IncrementForce(vCameraUp  * m_fJumpForce);
		}
		// Cap speed
		if (rb->GetVel().Length() > m_fMovementSpeed)
		{
			rb->SetVel(rb->GetVel().Normalize() * m_fMovementSpeed);
		}
		// Gun================================================================================
		// Fire--------------------------------------------------------------------------------
		if (Application::IsMousePressed(0))
		{
			this->m_CurrentGun->GetComponent<GunScript>()->PullTrigger(vCameraFront, dt);
		}
		else
		{
			this->m_CurrentGun->GetComponent<GunScript>()->ReleaseTrigger(vCameraFront);
		}
		//Reload--------------------------------------------------------------------------------
		if (KeyboardManager::GetInstance()->GetKeyTriggered("reload"))
		{
			m_CurrentGun->GetComponent<GunScript>()->Reload();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("Gun1"))
		{
			if (m_Guns.size() > 1)
			{
				m_CurrentGun->SetActive(false);
				m_CurrentGun = m_Guns.at(1);
				m_CurrentGun->SetActive(true);
			}
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("Gun0"))
		{
			if (m_Guns.size() > 0)
			{
				m_CurrentGun->SetActive(false);
				m_CurrentGun = m_Guns.at(0);
				m_CurrentGun->SetActive(true);
			}
		}
		Vector3 vCamPos = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS->GetPosition();
		Vector3 vGunPos = m_CurrentGun->TRANS->GetPosition();
		m_CurrentGun->TRANS->SetPosition(vCamPos);
		m_CurrentGun->TRANS->Translate(vCameraFront * 10);
		m_CurrentGun->TRANS->Translate(vRight * 5);
		m_CurrentGun->TRANS->Translate(-vCameraUp * 3);
		m_CurrentGun->TRANS->SetRotation(10, 0, 1, 0);
		if (m_CurrentGun->GetComponent<GunScript>()->IsEmpty())
		{
			m_CurrentGun->TRANS->Translate(0, -1, 0);
			m_CurrentGun->TRANS->SetRotation(10, 1, 1, 0);
		}
		// bob
		if (bMoved)
		{
			const float maxBob = 0.3f;
			static float speed = 0.07f * m_fMovementSpeed;
			static float offset = 0;
			if (offset > maxBob)
				speed = -fabs(speed);
			if (offset < -maxBob)
				speed = fabs(speed);
			float off = speed * (float)dt;
			GetCameraGO()->GetComponent<TransformComponent>()->TranslateRelative(0, off, 0);
			offset += off;

			m_CurrentGun->TRANS->Translate(0, offset, 0);
		}
	}

	// Camera================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
		SwitchView();

	if (KeyboardManager::GetInstance()->GetKeyTriggered("SwitchMap"))
	{
		SceneManager::GetInstance()->ChangeScene(new RojakAssignmentScene());
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("SwitchMap1"))
	{
		SceneManager::GetInstance()->ChangeScene(new RojakScene2());
	}
	return bMoved;
}
void ChengPlayerScript::UpdateGauntlet()
{
	// Gauntlet================================================================================
	//if (KeyboardManager::GetInstance()->GetKeyTriggered("triggerGauntlet"))
	if (Application::IsMousePressed(1))
		m_Gaunt->GetComponent<RenderComponent>()->SetActive(true);
	else
		m_Gaunt->GetComponent<RenderComponent>()->SetActive(false);
	if (m_Gaunt->IsActive())
	{
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGauntForward"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->RotateForward();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGauntBackward"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->RotateBackward();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("useGauntlet"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->Use();
		}
	}
}
void ChengPlayerScript::UpdateTilt()
{
	return;
	if (m_bState)
	{
		// Tilt
		if (Application::IsKeyPressed(VK_LEFT))
		{
			Vector3 GDir = { 1,0,1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-110, -85);
		}
		else if (Application::IsKeyPressed(VK_RIGHT))
		{
			Vector3 GDir = { -1,0,1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-70, -85);
		}
		else if (Application::IsKeyPressed(VK_UP))
		{
			Vector3 GDir = { 0,0,-1 };
			GDir.Normalize();
			GDir *= 100;
			WorldValues::DefaultGravity = GDir;
			TransformComponent* CamTrans = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS;
			CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -TRANS->GetPosition().z + 90);
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -60);
		}
		else if (Application::IsKeyPressed(VK_DOWN))
		{
			Vector3 GDir = { 0,0,1 };
			GDir.Normalize();
			GDir *= 150;
			WorldValues::DefaultGravity = GDir;
			TransformComponent* CamTrans = SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->TRANS;
			CamTrans->SetRelativePosition(CamTrans->GetRelativePosition().x, CamTrans->GetRelativePosition().y, -TRANS->GetPosition().z - 0);
			SceneManager::GetInstance()->GetScene()->GetCamera()->SetDir(-90, -90);
		}
	}
}
void ChengPlayerScript::UpdateConstrain()
{
	Constrain* con = GetComponent<Constrain>();
	if (!con)
		return;
	// Plains
	if (GetPosition().x > 0 && GetPosition().z > 0)
	{
		con->SetHeightMapData(DataContainer::GetInstance()->GetHeightMap("TerrainPlains"));
		// Underwater================================================================================
		if (TRANS->GetPosition().y < -15)
		{
			// Trigger underwater
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Underwater"));
		}
		else
		{
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
		}
	}
	if (GetPosition().x < 0 && GetPosition().z < 0)
	{
		con->SetHeightMapData(DataContainer::GetInstance()->GetHeightMap("TerrainTerrace"));
		//SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
	}
	if (GetPosition().x > 0 && GetPosition().z < 0)
	{
		con->SetHeightMapData(DataContainer::GetInstance()->GetHeightMap("TerrainSnow"));
		//SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
	}
	if (GetPosition().x < 0 && GetPosition().z > 0)
	{
		con->SetHeightMapData(DataContainer::GetInstance()->GetHeightMap("TerrainDesert"));
		//SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("HeatWave"));
	}
}
void ChengPlayerScript::RefillAmmo()
{
	for (unsigned i = 0; i < m_Guns.size(); ++i)
	{
		m_Guns.at(i)->GetComponent<GunScript>()->RefillAmmo();
	}
}
void ChengPlayerScript::Collide(GameObject* go)
{
	GunScript* gs = go->GetComponent<GunScript>();
	if (!gs)
		return;
	if (gs->GetHolding())
		return;
	m_Guns.push_back(go);
	go->SetActive(false);
	m_CurrentGun->SetActive(false);
	m_CurrentGun = go;
	m_CurrentGun->SetActive(true);
	m_CurrentGun->RENDER->SetBillboard(true);
}