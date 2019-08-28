#include "DefaultScene.h"
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
#include "InventoryScript.h"
#include "GunScript.h"
#include "PlayerStatsScript.h"
#include "ReticleScript.h"
#include "ParticleObserver.h"
#include "AdvancedParticleSpawnerScript.h"
#include "WinLoseScript.h"
#include "CheatScript.h"
#include "AbilityScript.h"
//Ob
#include "BossObserver.h"
//Obcom
#include "BossObserverCom.h"
//TMP
#include "ExplodeAugment.h"
#include "BlackHoleAugment.h"
#include "ReloadingAugment.h"
//systems
#include "PlayerData.h"

#define PLAYER_HEALTH 10000
DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}
void DefaultScene::Init()
{
	/// INIT ///
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	DataContainer* dataContainer = DataContainer::GetInstance();
	/// INIT ///
	/// Layers================================================================================
	m_GOM.CreateLayer(dataContainer->GetShader("Post"), "Post");
	m_GOM.CreateLayer(dataContainer->GetShader("EffectCRT"), "Post2");
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "Birds");
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "NoCollision");
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "Grass");
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "Particles");
	/// End Layers================================================================================
	/// RENDER ///
	go = m_GOM.AddGameObject(GetGO("Render"), "Post");
	go = m_GOM.AddGameObject(GetGO("Render2"), "Post2");
	/// RENDER ///
	/// Misc Data================================================================================
	Preferences::SetPref(Resources::PreferencesTerm::CamDist, "40");
	/// End Misc Data================================================================================
	/// Observers================================================================================
	GenericSubject::GetInstance()->AddObserver(new AudioObserver);
	GenericSubject::GetInstance()->AddObserver(new InteractablesObserver);
	GenericSubject::GetInstance()->AddObserver(new ParticleObserver);
	GenericSubject::GetInstance()->AddObserver(new BossObserver);
	/// End Observers================================================================================
	/// Audio================================================================================
	AudioManager::GetInstance()->PlayBGM("bgm_01.ogg", "low_synth");
	AudioManager::GetInstance()->SetBGMVolume(0, "low_synth");
	AudioManager::GetInstance()->QueueFade(1, 0.05f, "low_synth");
	AudioManager::GetInstance()->PlayBGM("bgm_02.ogg", "low_pad");
	AudioManager::GetInstance()->PlayBGM("bgm_03.ogg", "low_piano");
	AudioManager::GetInstance()->PlayBGM("bgm_04.ogg", "high_piano");
	AudioManager::GetInstance()->SetBGMVolume(0, "high_piano");
	/// End Audio================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");
	go->TRANS->SetPosition(1920 - 40, 1080 - 20, 25);
	/// Inventory--------------------------------------------------------------------------------
	// slots--------------------------------------------------------------------------------
	GameObject** InventorySlots;
	InventorySlots = new GameObject*[INVENTORY_SIZE];
	float height0 = 100;
	float height1 = 220;
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100, height0);
	InventorySlots[0] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110, height0);
	InventorySlots[1] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110 - 110, height0);
	InventorySlots[2] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100, height1);
	InventorySlots[3] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110, height1);
	InventorySlots[4] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110 - 110, height1);
	InventorySlots[5] = go;
	// customise--------------------------------------------------------------------------------
	std::vector<GameObject*> CustoSlots;
	Vector3 CustoPos(1920 - 200, 600);
	float fCustoDist = 100;
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos - Vector3(fCustoDist, 0, 0));
	go->RENDER->SetMesh(dataContainer->GetMesh("CraftingSlotMuzzle"));
	CustoSlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos + Vector3(0, fCustoDist, 0));
	go->RENDER->SetMesh(dataContainer->GetMesh("CraftingSlotScope"));
	CustoSlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos + Vector3(fCustoDist, 0, 0));
	go->RENDER->SetMesh(dataContainer->GetMesh("CraftingSlotStock"));
	CustoSlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos - Vector3(0, fCustoDist, 0));
	go->RENDER->SetMesh(dataContainer->GetMesh("CraftingSlotClip"));
	CustoSlots.push_back(go);
	/// End Inventory--------------------------------------------------------------------------------
	/// Player Stats--------------------------------------------------------------------------------
	// Stamina--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 940, 0);
	go->TRANS->SetScale(200, 50, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->RENDER->SetColor(0.7f, 0.7f, 0.7f);
	go->SetDisableDistance(-1);
	go->RENDER->SetRenderDistance(-1);
	//
	GameObject* StaminaBar = m_GOM.AddGameObject("UI");
	StaminaBar->TRANS->SetPosition(50, 940, 0);
	StaminaBar->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	StaminaBar->RENDER->SetColor(1, 1, 0);
	StaminaBar->SetDisableDistance(-1);
	StaminaBar->RENDER->SetRenderDistance(-1);
	//
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 970, 20);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Stamina"));
	go->RENDER->SetColor(1, 1, 1);
	go->SetDisableDistance(-1);
	go->RENDER->SetRenderDistance(-1);
	//
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 1030, 0);
	go->TRANS->SetScale(200, 50, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->RENDER->SetColor(0.7f, 0.7f, 0.7f);
	go->SetDisableDistance(-1);
	go->RENDER->SetRenderDistance(-1);
	//
	GameObject* HealthBar = m_GOM.AddGameObject("UI");
	HealthBar->TRANS->SetPosition(50, 1030, 0);
	HealthBar->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	HealthBar->RENDER->SetColor(1, 0.2f, 0.2f);
	HealthBar->SetDisableDistance(-1);
	HealthBar->RENDER->SetRenderDistance(-1);
	//
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 1060, 20);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "HEALTH"));
	go->RENDER->SetColor(1, 1.f, 1.f);
	go->SetDisableDistance(-1);
	go->RENDER->SetRenderDistance(-1);
	//
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(1920 / 3, 1040, 0);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->RENDER->SetColor(0.1f);
	go->TRANS->SetScale(1920 / 3, 12, 1);
	go->SetDisableDistance(-1);
	go->RENDER->SetRenderDistance(-1);
	//
	GameObject* BossBarText = m_GOM.AddGameObject("UI");
	BossBarText->TRANS->SetPosition(1920 / 2, 1000, 20);
	BossBarText->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Unitialised"));
	BossBarText->RENDER->SetColor(1, 1.f, 1.f);
	BossBarText->SetDisableDistance(-1);
	BossBarText->RENDER->SetRenderDistance(-1);
	//
	GameObject* BossBar = m_GOM.AddGameObject("UI");
	BossBar->TRANS->SetPosition(1920 / 3, 1040, 0);
	BossBar->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	BossBar->RENDER->SetColor(0.1f, 0.2f, 0.8f);
	BossBar->RENDER->SetRenderDistance(-1);
	//
	GameObject* AbilityUI = m_GOM.AddGameObject("UI");
	AbilityUI->TRANS->SetPosition(100, 100, 0);
	AbilityUI->TRANS->SetScale(200);
	switch (PlayerData::GetInstance()->GetCurrentAbility())
	{
	case PlayerData::eDASH:
		AbilityUI->AddComponent(new RenderComponent(dataContainer->GetMesh("AbilityDash")));
		break;
	case PlayerData::eGRENADE:
		AbilityUI->AddComponent(new RenderComponent(dataContainer->GetMesh("AbilityGrenade")));
		break;
	case PlayerData::eHEAL:
		AbilityUI->AddComponent(new RenderComponent(dataContainer->GetMesh("AbilityHeal")));
		break;
	case PlayerData::eSLOW_TIME:
		AbilityUI->AddComponent(new RenderComponent(dataContainer->GetMesh("AbilitySlowTime")));
		break;
	default:
		break;
	}
	AbilityUI->RENDER->SetLightEnabled(true);
	AbilityUI->RENDER->SetColor(0.1f, 0.2f, 0.8f);
	/// End Player Stats--------------------------------------------------------------------------------
	GameObject* CheatSheet = m_GOM.AddGameObject("UI");
	CheatSheet->AddComponent(new RenderComponent(dataContainer->GetMesh("CheatSheet")));
	CheatSheet->TRANS->SetPosition(1400, 400, 0);
	CheatSheet->TRANS->SetScale(500);
	CheatSheet->RENDER->SetRenderDistance(-1);
	/// End UI================================================================================
	/// Systems================================================================================
	GameObject* BossSpawner = m_GOM.AddGameObject(dataContainer->GetGameObject("BossSpawner"), "NoCollision");
	BossSpawner->AddComponent(new BossObserverCom);
	/// Ends Systems================================================================================
	/// Player================================================================================
	// Reticle
	GameObject* ret = m_GOM.AddGameObject(GetGO("Reticle"), "NoCollision");
	//Gun------------------------------------------------------------------------------------
	GameObject* Gun = dataContainer->GetGameObject("Gun");
	Gun->TRANS->SetRelativePosition(1, 0.75, 1);
	Gun->TRANS->SetRelativeRotation(25, Vector3(0, 1, 0));

	GameObject* tmp;
	GunScript* gs = Gun->GUN;

	tmp = dataContainer->GetGameObject("Muzzle");
	tmp->PART->SetAugment(new ExplodeAugment);
	tmp->PART->GetAugment()->SetEntityReference(tmp->GetComponent<PlayerScript>());
	tmp->PART->GetAugment()->SetGunReference(gs);
	
	Gun->AddChild(tmp);
	Gun->GUN->EquipPart(tmp, WeaponPartScript::SLOT_TYPE::MUZZLE);

	tmp = dataContainer->GetGameObject("Muzzle");
	tmp->PART->SetAugment(new ExplodeAugment);
	tmp->PART->GetAugment()->SetEntityReference(tmp->GetComponent<PlayerScript>());
	tmp->PART->GetAugment()->SetGunReference(gs);

	Gun->AddChild(tmp);
	Gun->GUN->EquipPart(tmp, WeaponPartScript::SLOT_TYPE::MUZZLE);

	// Grenade-------------------------------------------------------------------------------
	GameObject* grenade = dataContainer->GetGameObjectRaw("Grenade");
	grenade->TRANS->SetRelativePosition(0, 1, 1);
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject();
	m_Player = Player;
	Player->AddComponent(new PlayerScript(dataContainer->GetBehaviour("Player"), ret, Gun, grenade, Stats(PLAYER_HEALTH)));
	Player->AddChild(Gun);
	Player->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	Player->AddComponent(new RenderComponent(dataContainer->GetMesh("Player")));
	Player->RIGID->SetMat(1.05f, 0.f);
	Player->RENDER->SetActive(true);
	Player->TRANS->SetPosition(0, 18, 0);
	Player->AddComponent(new InventoryScript(Gun, InventorySlots, CustoSlots, ret));
	Player->AddComponent(new PlayerStatsScript(Player, StaminaBar, HealthBar, Gun, dataContainer->GetGameObjectRaw("BulletUI"), BossSpawner, BossBar, BossBarText));
	Player->AddComponent(new MapSpawningScript());
	Player->AddComponent(new AdvancedParticleSpawnerScript(AdvancedParticleSpawnerScript::CIRCULAR, 12, true, dataContainer->GetGameObjectRaw("particledestroy"), 100, Vector3(), 0.f, "Particles", 10.f));
	Player->AddComponent(new WinLoseScript());
	Player->GetComponent<EntityScript>()->SetCanDie(true);
	Player->AddComponent(new AbilityScript(PlayerData::GetInstance()->GetAbility(), AbilityUI));
	Player->AddComponent(new CheatScript(CheatSheet));
	/// End Player================================================================================
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(Player));
	m_CameraGO->AddComponent(new CameraComponent);
	// m_CameraGO->AddChild(go2);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 100;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(false);
	/// End Create Camera================================================================================
	/// Entities================================================================================
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("Bird"), "Birds");
	go->TRANS->SetPosition(3, 24.f, 0);
	/// End Entities================================================================================
	/// Interactables================================================================================
	// Treasure--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("treasurebox"));
	go->TRANS->SetPosition(20, 18.5, 20);
	// boulder--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("boulder"));
	go->TRANS->SetPosition(10, 19, 20);
	// fliprock--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("fliprock"));
	go->TRANS->SetPosition(0, 19, 20);
	/// End Interactables================================================================================
}