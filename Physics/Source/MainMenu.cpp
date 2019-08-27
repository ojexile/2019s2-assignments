#include "MainMenu.h"
#include "GenericSubject.h"
#include "AudioObserver.h"
#include "AudioManager.h"
#include "ChunkCollider.h"
#include "InteractablesObserver.h"
#include "InteractableObCom.h"
#include "PlayerScript.h"
#include "Utility.h"
#include "CameraScript.h"
#include "MapSpawningScript.h"
#include "GunScript.h"
#include "PlayerStatsScript.h"
#include "ReticleScript.h"
#include "ParticleObserver.h"
#include "AdvancedParticleSpawnerScript.h"
//Ob
#include "BossObserver.h"
//Obcom
#include "BossObserverCom.h"
#include "GameObjectManager.h"
// Components
#include "CameraComponent.h"
#include "DataContainer.h"
#include "BiomeComponent.h"
#include "UIButtonComponent.h"
// Scripts
#include "MenuButtonsScript.h"
//
#include "PlayerData.h"
MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}
void MainMenu::Init()
{
	///
	PlayerData::GetInstance()->Load("Cheng", "69");
	PlayerData::GetInstance()->Save();
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
	GenericSubject::GetInstance()->AddObserver(new AudioObserver);
	GenericSubject::GetInstance()->AddObserver(new InteractablesObserver);
	GenericSubject::GetInstance()->AddObserver(new ParticleObserver);
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
	// Play--------------------------------------------------------------------------------
	GameObject* PlayButt = m_GOM.AddGameObject(GetGO("MenuButton"), "UI");
	PlayButt->TRANS->SetPosition(50 + 50, 1080 - 1080 / 6 + 40);
	PlayButt->SetDisableDistance(-1);
	//
	GameObject* Ability0 = m_GOM.AddGameObject(GetGO("Ability0"), "UI");
	Ability0->TRANS->SetPosition(50 + 50 + 150, 1080 - 1080 / 6 + 40);
	Ability0->SetActive(false);
	//
	GameObject* Ability1 = m_GOM.AddGameObject(GetGO("Ability1"), "UI");
	Ability1->TRANS->SetPosition(50 + 50 + 150 + 150, 1080 - 1080 / 6 + 40);
	Ability1->SetActive(false);
	//
	GameObject* PlayText = m_GOM.AddGameObject("UI");
	PlayText->TRANS->SetPosition(50, 1080 - 1080 / 6, 80);
	PlayText->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Play"));
	PlayText->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	PlayText->SetDisableDistance(-1);
	// Tutorial--------------------------------------------------------------------------------
	GameObject* TutorialButt = m_GOM.AddGameObject(GetGO("MenuButton"), "UI");
	TutorialButt->TRANS->SetPosition(50 + 50, 1080 - 1080 / 6 * 2 + 40);
	TutorialButt->SetDisableDistance(-1);
	//
	GameObject* TutorialText = m_GOM.AddGameObject("UI");
	TutorialText->TRANS->SetPosition(50, 1080 - 1080 / 6 * 2, 80);
	TutorialText->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Tutorial"));
	TutorialText->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	TutorialText->SetDisableDistance(-1);
	//
	GameObject* TutBox = m_GOM.AddGameObject("UI");
	TutBox->TRANS->SetPosition(1920 / 2 + 500, 1080 / 2);
	TutBox->AddComponent(new RenderComponent(dataContainer->GetMesh("QuadCentered")));
	TutBox->SetDisableDistance(-1);
	TutBox->TRANS->SetScale(600, 800, 1);
	TutBox->SetActive(false);
	// Quit--------------------------------------------------------------------------------
	GameObject* QuitButt = m_GOM.AddGameObject(GetGO("MenuButton"), "UI");
	QuitButt->TRANS->SetPosition(50 + 50, 1080 - 1080 / 6 * 3 + 40);
	QuitButt->SetDisableDistance(-1);
	//
	GameObject* QuitText = m_GOM.AddGameObject("UI");
	QuitText->TRANS->SetPosition(50, 1080 - 1080 / 6 * 3, 80);
	QuitText->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Quit"));
	QuitText->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	QuitText->SetDisableDistance(-1);
	// Init Menu Buttons================================================================================
	go = m_GOM.AddGameObject();
	go->AddComponent(new MenuButtonsScript(PlayText, PlayButt, QuitText, QuitButt,
		TutorialText, TutorialButt, TutBox, Ability0, Ability1));
	go->SetDisableDistance(-1);
	//
	/// End UI================================================================================
	/// Player================================================================================
	//Gun------------------------------------------------------------------------------------
	GameObject* Gun = dataContainer->GetGameObject("Gun");
	Gun->TRANS->SetRelativePosition(1, 0.75, 1);
	//TMP------------------------------------------------------------------------------------
	GameObject* muz = dataContainer->GetGameObject("Muzzle");
	Gun->AddChild(muz);
	Gun->GUN->EquipPart(muz, WeaponPartScript::SLOT_TYPE::MUZZLE);
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject();
	m_Player = Player;
	Player->AddComponent(new PlayerScript(nullptr, nullptr, Gun, nullptr, Stats()));
	Player->AddChild(Gun);
	Player->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	Player->AddComponent(new RenderComponent(dataContainer->GetMesh("Player")));
	Player->RIGID->SetMat(1.05f, 0.f);
	Player->RENDER->SetActive(true);
	Player->TRANS->SetPosition(0, 18, 0);
	Player->AddComponent(new MapSpawningScript());
	Player->GetComponent<EntityScript>()->SetCanDie(false);
	/// End Player================================================================================
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(Player));
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
	/// End Create Camera================================================================================
}