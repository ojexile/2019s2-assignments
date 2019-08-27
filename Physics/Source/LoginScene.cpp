#include "LoginScene.h"
// Scripts--------------------------------------------------------------------------------
#include "LoginScript.h"
// Systems--------------------------------------------------------------------------------
#include "DataContainer.h"
#include "AudioManager.h"
#include "Utility.h"

LoginScene::LoginScene()
{
}

LoginScene::~LoginScene()
{
}

void LoginScene::Init()
{
	/// Init================================================================================
	DataContainer* dataContainer = DataContainer::GetInstance();
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "Birds");
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "NoCollision");
	m_GOM.CreateLayer(dataContainer->GetShader("PassThrough"), "Post");
	m_GOM.CreateLayer(dataContainer->GetShader("PassThrough"), "Post2");
	GameObject* go = nullptr;
	go = m_GOM.AddGameObject(GetGO("Render"), "Post");
	go = m_GOM.AddGameObject(GetGO("Render2"), "Post2");
	GameObject* go2 = nullptr;
	Preferences::SetPref(Resources::PreferencesTerm::CamDist, "80");
	/// Observers================================================================================
	/// Audio================================================================================
	AudioManager::GetInstance()->PlayBGM("bgm_01.ogg", "low_synth");
	AudioManager::GetInstance()->SetBGMVolume(0, "low_synth");
	AudioManager::GetInstance()->QueueFade(1, 0.05f, "low_synth");
	AudioManager::GetInstance()->PlayBGM("bgm_02.ogg", "low_pad");
	AudioManager::GetInstance()->PlayBGM("bgm_03.ogg", "low_piano");
	AudioManager::GetInstance()->PlayBGM("bgm_04.ogg", "high_piano");
	AudioManager::GetInstance()->SetBGMVolume(0, "high_piano");
	/// Layers================================================================================
	/// End Layers================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");
	go->TRANS->SetPosition(1920 - 40, 1080 - 20, 25);
	// Title--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(1920 / 2 + 200, 10, 120);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "TITLE OF GAME"));
	go->RENDER->SetColor({ 0.4f,1.f,0.8f });
	go->SetDisableDistance(-1);
	/// Background--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("QuadCentered")));
	go->TRANS->SetPosition(1920 / 2, 1080 / 2);
	go->TRANS->SetScale(1920, 1080, 1);
	go->RENDER->SetColor(1, 1, 1);
	/// Login--------------------------------------------------------------------------------
	// Input--------------------------------------------------------------------------------
	GameObject* UserInput = m_GOM.AddGameObject("UI");
	UserInput->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), ""));
	UserInput->TRANS->SetPosition(1920 / 2 + 100 + 50, 1080 / 2, 50);
	//
	GameObject* PassInput = m_GOM.AddGameObject("UI");
	PassInput->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), ""));
	PassInput->TRANS->SetPosition(1920 / 2 + 100 + 50, 1080 / 2 - 200, 50);
	//
	go = m_GOM.AddGameObject("UI");
	go->AddComponent(new LoginScript(UserInput, PassInput));
	// User--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(1920 / 2, 1080 / 2, 50);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "User::"));
	go->RENDER->SetColor({ 0.4f,1.f,0.8f });
	go->SetDisableDistance(-1);
	// Pass--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(1920 / 2, 1080 / 2 - 200, 50);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Pass::"));
	go->RENDER->SetColor({ 0.4f,1.f,0.8f });
	go->SetDisableDistance(-1);
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraComponent);
	// m_CameraGO->AddChild(go2);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_CUSTOM_ORTHO);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 100;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(true);
}