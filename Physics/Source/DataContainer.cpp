#include "DataContainer.h"
#include <time.h>
// Components================================================================================
#include "Constrain.h"
#include "MeshController.h"
#include "Rigidbody.h"
#include "UIButtonComponent.h"
// Scripts--------------------------------------------------------------------------------
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "FPSScript.h"
#include "ProjectileScript.h"
#include "ReticleScript.h"
#include "PlayerScript.h"
#include "GunScript.h"
#include "GrenadeScript.h"
#include "LootScript.h"
#include "DestructibleEntityScript.h"
#include "FlipEntityScript.h"
#include "InteractableObCom.h"
#include "SpawnLootScript.h"
#include "DebrisSpawningScript.h"
#include "ReloadUIScript.h"
#include "AdvancedParticleSpawnerScript.h"
#include "BlackholeScript.h"
#include "SuicideNoteScript.h"
#include "BirdWingScript.h"
//
#include "ScalePatternScript.h"

#include "WeaponPartScript.h"
//States
#include "StandingState.h"
#include "IdleState.h"
#include "MeleeCombatState.h"
#include "FleeState.h"
//
#include "AIStatesList.h"
#include "AIEntityScript.h"
//Entity Library
#include "Entity_Library.h"
DataContainer::DataContainer()
{
	m_bInitialsed = false;
}
void DataContainer::Init()
{
	clock_t begin = clock();
	if (m_bInitialsed)
	{
		DEFAULT_LOG("Attempted re-init of datacontainer");
		return;
	}
	m_bInitialsed = true;

	InitTextures();
	InitMeshes();
	InitTerrain();
	InitBehaviour();
	InitGO();
	InitChunks();
	InitShaders();
	Entity_Library::GetInstance()->Init();
	m_bInitialsed = true;

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	// CHENG_LOG("Time to load container: ", std::to_string(elapsed_secs));
}

void DataContainer::InitChunks()
{
	m_map_Chunks["archway"] = new ChunkData("Content/chunks/1x1_archway.chunk");
	m_map_Chunks["goldmine"] = new ChunkData("Content/chunks/1x2_goldmine.chunk");
	m_map_Chunks["smallhouse"] = new ChunkData("Content/chunks/1x1_smallhouse.chunk");
	m_map_Chunks["bazaar1"] = new ChunkData("Content/chunks/1x1_bazaar1.chunk");
	m_map_Chunks["bazaar1_1"] = new ChunkData("Content/chunks/1x1_bazaar1.chunk", 1);
	m_map_Chunks["bazaar1_2"] = new ChunkData("Content/chunks/1x1_bazaar1.chunk", 2);
	m_map_Chunks["bazaar1_3"] = new ChunkData("Content/chunks/1x1_bazaar1.chunk", 3);
	m_map_Chunks["wellspring"] = new ChunkData("Content/chunks/1x1_wellspring.chunk");
	m_map_Chunks["wellspring_1"] = new ChunkData("Content/chunks/1x1_wellspring.chunk", 1);
	m_map_Chunks["walledoff"] = new ChunkData("Content/chunks/1x1_walledoff.chunk");
	m_map_Chunks["walledoff_1"] = new ChunkData("Content/chunks/1x1_walledoff.chunk", 1);
	m_map_Chunks["walledoff_2"] = new ChunkData("Content/chunks/1x1_walledoff.chunk", 2);
	m_map_Chunks["walledoff_3"] = new ChunkData("Content/chunks/1x1_walledoff.chunk", 3);
	m_map_Chunks["barline"] = new ChunkData("Content/chunks/1x2_barline.chunk");
	m_map_Chunks["barline_1"] = new ChunkData("Content/chunks/1x2_barline.chunk", 3);
	m_map_Chunks["barline_2"] = new ChunkData("Content/chunks/1x2_barline.chunk", 3);
	m_map_Chunks["barline_3"] = new ChunkData("Content/chunks/1x2_barline.chunk", 3);
}

void DataContainer::InitTextures()
{
	m_map_Textures["Text"] = LoadTGA("calibri");
	m_map_Textures["Sky"] = LoadTGA("sky");
	m_map_Textures["Cube"] = LoadTGA("Cube");
	m_map_Textures["Dirt"] = LoadTGA("dirt");
	m_map_Textures["grassdirt"] = LoadTGA("grassdirt");
	m_map_Textures["GrassDirt"] = LoadTGA("grassdirt");
	m_map_Textures["Colors"] = LoadTGA("colors");
	m_map_Textures["snow"] = LoadTGA("snow");
	m_map_Textures["beachy"] = LoadTGA("beachy");
	m_map_Textures["gb"] = LoadTGA("gameboy");
	m_map_Textures["crimson"] = LoadTGA("crimson");
	m_map_Textures["void"] = LoadTGA("void");
	m_map_Textures["gray"] = LoadTGA("gray");
	m_map_Textures["mesa"] = LoadTGA("mesa");
	m_map_Textures["Ball"] = LoadTGA("Ball");

	m_map_Textures["Revolver"] = LoadTGA("revolver");
	m_map_Textures["Muzzle"] = LoadTGA("muzzle");

	m_map_Textures["CraftingSlotMuzzle"] = LoadTGA("CraftingSlotMuzzle");
	m_map_Textures["CraftingSlotScope"] = LoadTGA("CraftingSlotScope");
	m_map_Textures["CraftingSlotStock"] = LoadTGA("CraftingSlotStock");
	m_map_Textures["CraftingSlotClip"] = LoadTGA("CraftingSlotClip");
	m_map_Textures["InventorySlot"] = LoadTGA("InventorySlot");

	m_map_Textures["UIBullet"] = LoadTGA("UIBullet");

	m_map_Textures["plaintree"] = LoadTGA("plain_tree");
	m_map_Textures["snowtree"] = LoadTGA("snow_tree");

	m_map_Textures["particleSquareBorder"] = LoadTGA("particleSquareBorder");
	m_map_Textures["particleHexagon"] = LoadTGA("particleHexagon");
}
void DataContainer::InitMeshes()
{
	/// Meshes================================================================================
	/// DO NOT REMOVE--------------------------------------------------------------------------------
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16)->AddTexture("Text");
	//--------------------------------------------------------------------------------
	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 6, 400, 6, 6)->AddTexture("Sky");

	m_map_Meshes["Axis"] = MeshBuilder::GenerateAxes("Axes", 1000, 1000, 1000);

	m_map_Meshes["Cube"] = MeshBuilder::GenerateOBJ("Cube")->AddTexture("Cube");

	m_map_Meshes["Ball"] = MeshBuilder::GenerateOBJ("Ball")->AddTexture("InventorySlot");

	m_map_Meshes["Stamina"] = MeshBuilder::GenerateOBJ("Stamina")->AddTexture("InventorySlot");

	m_map_Meshes["Muzzle"] = MeshBuilder::GenerateOBJ("Muzzle")->AddTexture("Muzzle");

	m_map_Meshes["Clip"] = MeshBuilder::GenerateOBJ("Clip")->AddTexture("Revolver");

	m_map_Meshes["Grip"] = MeshBuilder::GenerateOBJ("Muzzle")->AddTexture("Revolver");

	m_map_Meshes["Scope"] = MeshBuilder::GenerateOBJ("Muzzle")->AddTexture("Revolver");

	m_map_Meshes["Player"] = MeshBuilder::GenerateOBJ("Player")->AddTexture("Cube");

	m_map_Meshes["Reticle"] = MeshBuilder::GenerateOBJ("Reticle");

	//Mesh
	m_map_Meshes["plaintree"] = MeshBuilder::GenerateOBJ("plain_tree", true);
	GetMeshBiomed("plaintree")
		->AddTexture("plaintree", BiomeComponent::BIOME_PLAINS)
		->AddTexture("snowtree", BiomeComponent::BIOME_SNOW);

	m_map_Meshes["Gun"] = MeshBuilder::GenerateOBJ("gun")->AddTexture("Revolver");

	m_map_Meshes["Grenade"] = MeshBuilder::GenerateOBJ("Ball")->AddTexture("InventorySlot");

	m_map_Meshes["UIInventory"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("InventorySlot");

	m_map_Meshes["CraftingSlotMuzzle"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("CraftingSlotMuzzle");
	m_map_Meshes["CraftingSlotScope"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("CraftingSlotScope");
	m_map_Meshes["CraftingSlotStock"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("CraftingSlotStock");
	m_map_Meshes["CraftingSlotClip"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("CraftingSlotClip");
	m_map_Meshes["InventorySlot"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("InventorySlot");

	m_map_Meshes["UIBullet"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("UIBullet");

	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuadLeftCentered({}, 1);

	m_map_Meshes["QuadCentered"] = MeshBuilder::GenerateQuad("", {}, 1);

	m_map_Meshes["ItemInfo"] = MeshBuilder::GenerateQuad("", { 1,1,1 }, 5);

	m_map_Meshes["particlequad"] = MeshBuilder::GenerateQuad("particlequad", {}, 1.f)->AddTexture("particleSquareBorder");
	m_map_Meshes["Fish"] = MeshBuilder::GenerateOBJ("Fish");

	m_map_Meshes["Cow"] = MeshBuilder::GenerateOBJ("mccow");

	m_map_Meshes["boulder"] = MeshBuilder::GenerateOBJ("Cube")->AddTexture("UIBullet");

	m_map_Meshes["fliprock"] = MeshBuilder::GenerateOBJ("fliprock");

	m_map_Meshes["chest"] = MeshBuilder::GenerateOBJ("Cube");

	m_map_Meshes["BirdBody"] = MeshBuilder::GenerateOBJ("Bird/Body");
	m_map_Meshes["WingLeft"] = MeshBuilder::GenerateOBJ("Bird/WingLeft");
	m_map_Meshes["WingRight"] = MeshBuilder::GenerateOBJ("Bird/WingRight");

	m_map_Meshes["EnemyReticle"] = MeshBuilder::GenerateOBJ("EnemyReticle");
	m_map_Meshes["Fox"] = MeshBuilder::GenerateOBJ("Fox");
	m_map_Meshes["Chick"] = MeshBuilder::GenerateOBJ("Chick");
}
void DataContainer::InitTerrain()
{
	/// Terrain================================================================================
	// Plains--------------------------------------------------------------------------------
	MeshBiomed* mesh1 = GenerateTerrainBiomed("TerrainPlains", "heightmapPlains", { 200,60,200 }, { 0,0,0 })
		->AddTexture("Cube", BiomeComponent::BIOME_PLAINS);
	//->AddTexture(("grassdirt"), BiomeComponent::BIOME_FLAT);
}
void DataContainer::InitGO()
{
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	///================================================================================
	// Reticle--------------------------------------------------------------------------------
	//go = new GameObject();
	//m_map_GO["Reticle"] = go;
	//go->AddComponent(new RenderComponent(GetMesh("Reticle")));
	//go->RENDER->SetColor(0, 1, 1);
	//go->AddComponent(new ReticleScript);
	//Bullet--------------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["Bullet"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->RIGID->SetMass(0.005f);
	go->RIGID->SetMat(0.9f, 1);
	go->AddComponent(new ProjectileScript(1.0, 30.0));
	/// Weapon Parts================================================================================
	go = new GameObject();
	m_map_GO["Muzzle"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Muzzle")));
	go->AddComponent(new WeaponPartScript(WeaponPartScript::MUZZLE, 0.5, 1));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->RIGID->SetResponseActive(false);
	go = new GameObject();
	m_map_GO["Clip"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Clip")));
	go->AddComponent(new WeaponPartScript(WeaponPartScript::CLIP, 2.0, 50));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetResponseActive(false);
	go = new GameObject();
	m_map_GO["Scope"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Scope")));
	go->AddComponent(new WeaponPartScript(WeaponPartScript::SCOPE, 0.5, 1));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetResponseActive(false);
	go = new GameObject();
	m_map_GO["Grip"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Grip")));
	go->AddComponent(new WeaponPartScript(WeaponPartScript::GRIP, 2.0, 50));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetResponseActive(false);
	// Gun--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Gun"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Gun")));
	go->AddComponent(new GunScript(GetGameObject("Bullet")));
	go2 = new GameObject;
	go->AddChild(go2);
	go2->AddComponent(new RenderComponent(GetMesh("QuadCentered")));
	go2->TRANS->SetRelativePosition(0, 2, 0);
	go2->RENDER->SetColor(1, 1, 1);
	go2->RENDER->Set3DBillboard(true);
	go2->AddComponent(new ReloadUIScript());
	// Grenade----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Grenade"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->TRANS->SetScale(0.5);
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	go->RIGID->SetMass(0.25f);
	go->RIGID->SetMat(2.f, 0.f);
	go->AddComponent(new GrenadeScript(3.0, 10.0, 2));
	// Loot------------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Loot"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	///Enemies-----------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["EnemyReticle"] = go;
	go->AddComponent(new RenderComponent(GetMesh("EnemyReticle")));
	go->TRANS->SetRelativePosition(0.f, 1.f, 0.f);
	// Base--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["BaseEnemy"] = go;
	go->AddChild(GetGameObject("EnemyReticle"));
	go->AddComponent(new RenderComponent(GetMesh("Fish")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->AddComponent(new AIEntityScript(GetBehaviour("Default"), &AIStatesList::Melee));
	go->AddComponent(new LootScript());
	// Melee--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Melee"] = go;
	go->AddChild(GetGameObject("EnemyReticle"));
	go->AddComponent(new RenderComponent(GetMesh("Fish")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->AddComponent(new AIEntityScript(GetBehaviour("Default"), &AIStatesList::Melee));
	go->AddComponent(new LootScript());
	// Range-----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Ranged"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Cow")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->AddComponent(new AIEntityScript(GetBehaviour("Default"), &AIStatesList::Ranged, Stats(100, 0, 100, 0, 80, 20, 2000, 12)));
	go2 = GetGameObject("Gun");
	go2->TRANS->SetRelativeRotation(-90, 0, 1, 0);
	go->AddChild(go2);
	go->AddComponent(new LootScript());
	// Boss================================================================================
	go = new GameObject;
	m_map_GO["Boss"] = go;
	go->AddChild(GetGameObject("EnemyReticle"));
	go->AddComponent(new RenderComponent(GetMesh("Cow")));
	go->TRANS->SetScale(3);
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->AddComponent(new AIEntityScript(GetBehaviour("Default"), &AIStatesList::Boss, Stats(500, 0, 100, 0, 80, 20, 2000, 16)));
	go->AddComponent(new LootScript());
	// Shockwave
	go = new GameObject;
	m_map_GO["Shockwave"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->TRANS->SetScale(0.5f);
	go->RENDER->SetColor(1, 0, 0);
	go->AddComponent(new BlackholeScript(-0.01f, 4));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->RIGID->LockYAxis(true);
	go->RIGID->SetMat(0.25f, 0);
	go->AddComponent(new SuicideNoteScript(5.f));
	// Animals--------------------------------------------------------------------------------
	// Cow-----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Cow"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Cow")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->AddChild(GetGameObject("EnemyReticle"));
	go->AddComponent(new AIEntityScript(GetBehaviour("Default"), &AIStatesList::Flee, Stats(100, 0, 100, 0, 80, 20, 2000, 12)));
	// go->AddComponent(new LootScript());
	go = new GameObject;
	m_map_GO["Bird"] = go;
	go->AddComponent(new RenderComponent(GetMesh("BirdBody")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	go->RIGID->LockYAxis(true);
	go->AddComponent(new AIEntityScript(GetBehaviour("Bird"), &AIStatesList::Flee, Stats(100, 0, 100, 0, 80, 20, 2000, 2)));
	go->AddChild(GetGameObject("EnemyReticle"));
	go->AddComponent(new BirdWingScript);
	go2 = new GameObject;
	go->AddChild(go2);
	go2->AddComponent(new RenderComponent(GetMesh("WingLeft")));
	go2->TRANS->SetRelativePosition(0.378f, 0.458f, 0.082f);
	go2 = new GameObject;
	go->AddChild(go2);
	go2->AddComponent(new RenderComponent(GetMesh("WingRight")));
	go2->TRANS->SetRelativePosition(-0.378f, 0.458f, 0.082f);

	// Fish-----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Fish"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Fish")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->AddComponent(new AIEntityScript(GetBehaviour("Default"), &AIStatesList::Flee, Stats(50, 0, 100, 0, 80, 20, 2000, 12)));
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["FPS"] = go;
	go->AddComponent(new FPSScript);
	go->TRANS->SetPosition(50, 10, 25);
	go->AddComponent(new RenderComponent(GetMesh("Text"), "0"));
	go->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	go->SetDisableDistance(10000);
	// InventorySlot--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["InventorySlot"] = go;
	go->AddComponent(new UIButtonComponent);
	go->AddComponent(new RenderComponent(GetMesh("UIInventory")));
	go->RENDER->SetLightEnabled(false);
	go->TRANS->SetScale(100);
	go->SetDisableDistance(10000);
	// CustomiseSlot--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["CustomiseSlot"] = go;
	go->AddComponent(new UIButtonComponent);
	go->AddComponent(new RenderComponent());
	go->RENDER->SetLightEnabled(false);
	go->TRANS->SetScale(100);
	go->SetDisableDistance(10000);
	// BulletUI--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["BulletUI"] = go;
	go->AddComponent(new UIButtonComponent);
	go->AddComponent(new RenderComponent(GetMesh("UIBullet")));
	go->RENDER->SetLightEnabled(false);
	go->TRANS->SetScale(50, 20, 1);
	go->SetDisableDistance(10000);
	// ItemInfo--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["ItemInfo"] = go;
	go->AddComponent(new RenderComponent(GetMesh("ItemInfo")));
	go->RENDER->Set3DBillboard(true);
	/// Interactabes/Foilage================================================================================
	go = new GameObject();
	m_map_GO["particledestroy"] = go;
	go->AddComponent(new RenderComponent(GetMesh("particlequad")));
	//go->GetComponent<RenderComponent>()->SetColor(1.f, 0.6f, 0.2f);
	go->GetComponent<RenderComponent>()->SetBillboard(true);
	go->RENDER->SetLightEnabled(false);
	//go->TRANS->SetScale(0.5f);
	//go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->AddComponent(new ParticleScript(0.5f, Vector3(0.f, -0.1f, 0.f), Vector3(0.f, -1.f, 0.f), Vector3(), Vector3(), Vector3()));
	go->PARTICLE->SetRot({ 80.f, 80.f, 80.f });
	go->AddComponent(new ScalePatternScript(ScalePatternScript::SHRINK, 1.f, 0.5f));

	go = new GameObject();
	m_map_GO["particlespawnerdestroy"] = go;
	go->AddComponent(new AdvancedParticleSpawnerScript(AdvancedParticleSpawnerScript::SPEW, 20, true, m_map_GO["particledestroy"], 100, Vector3(), 0.f, "Default", 10.f));

	go = new GameObject();
	m_map_GO["plaintree"] = go;
	go->AddComponent(new RenderComponent(GetMeshBiomed("plaintree")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->AddComponent(new DestructibleEntityScript());
	go->AddComponent(new InteractableObCom());
	static_cast<FlipEntityScript*>(go->AddComponent(new FlipEntityScript()))->SetMaxElapsedTime(1.f);

	go = new GameObject();
	m_map_GO["fliprockrender"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Cube")));
	//go->AddComponent(new InteractableObCom());
	go = new GameObject();
	m_map_GO["fliprock"] = go;
	go->TRANS->SetScale(2.f, 1.f, 2.f);
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	//go->RIGID->SetMat(0.9f, 0);
	go->AddComponent(new InteractableObCom());
	go->AddComponent(new DestructibleEntityScript(""));
	static_cast<FlipEntityScript*>(
		go->AddComponent(new FlipEntityScript()))->SetMaxElapsedTime(0.5f);
	go->AddComponent(new AdvancedParticleSpawnerScript(AdvancedParticleSpawnerScript::SPEW, 20, true, m_map_GO["particledestroy"], 100, Vector3(), 0.f, "Default", 10.f));

	go->AddChild(GetGameObject("fliprockrender"));

	go = new GameObject();
	m_map_GO["treasurebox"] = go;
	go->AddComponent(new InteractableObCom());
	go->AddComponent(new RenderComponent(GetMesh("chest")));
	go->RENDER->SetColor(1.f, 0.8f, 0.f);
	go->AddComponent(new SpawnLootScript());
	go->TRANS->SetScale(1, 1, 1);
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));

	go = new GameObject();
	m_map_GO["treasureball"] = go;
	go->AddComponent(new LootScript());
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetMat(1.f, 0);
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->TRANS->SetScale(1.f);

	go = new GameObject();
	m_map_GO["boulder"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->RENDER->SetColor({ 0.1f,0.1f,0.1f });
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetMass(1000.f);
	go->TRANS->SetScale(2.f);
	go->AddComponent(new DestructibleEntityScript("RockDied"));
	//go->GetComponent<DestructibleEntityScript>()->GetBaseStats()->SetMaxHealth(1);
	go->AddComponent(new DebrisSpawningScript("boulder2", 2, 2));
	go->AddComponent(new AdvancedParticleSpawnerScript(AdvancedParticleSpawnerScript::SPEW, 20, true, m_map_GO["particledestroy"], 100, Vector3(), 0.f, "Default", 10.f));

	go = new GameObject();
	m_map_GO["boulder2"] = go;
	go->AddComponent(new RenderComponent(GetMesh("boulder")));
	go->RENDER->SetColor(0.1f, 0.1f, 0.1f);
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetMass(10.f);
	go->TRANS->SetScale(1.f);
	go->AddComponent(new EntityScript());
}
void  DataContainer::InitShaders()
{
	m_map_Shaders["Default"] = LoadShaders("Flare", "Flare");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
}
void DataContainer::InitBehaviour()
{
	m_map_Behaviour["Player"] = new Behaviour(new StandingState);
	m_map_Behaviour["Default"] = new Behaviour(&AIStatesList::Idle);
	m_map_Behaviour["Bird"] = new Behaviour(&AIStatesList::BirdIdle);
}
DataContainer::~DataContainer()
{
	std::map<std::string, Mesh*>::iterator it;
	for (it = m_map_Meshes.begin(); it != m_map_Meshes.end(); it++)
	{
		// it->first == key
		// it->second == value
		delete it->second;
	}
	m_map_Meshes.clear();
	std::map<std::string, AnimatedMesh*>::iterator it2;
	for (it2 = m_map_Animated.begin(); it2 != m_map_Animated.end(); it2++)
	{
		// it->first == key
		// it->second == value
		delete it2->second;
	}
	m_map_Animated.clear();
	std::map<std::string, GameObject*>::iterator it3;
	for (it3 = m_map_GO.begin(); it3 != m_map_GO.end(); it3++)
	{
		// it->first == key
		// it->second == value
		delete it3->second;
	}
	m_map_GO.clear();
	for (it3 = m_map_GO.begin(); it3 != m_map_GO.end(); it3++)
	{
		// it->first == key
		// it->second == value
		delete it3->second;
	}
	m_map_GO.clear();
	for (auto const& x : m_map_HeightMaps)
	{
		delete x.second;
	}
	m_map_HeightMaps.clear();
	//for (auto const& x : m_map_Chunks)
	//{
	//	delete x.second;
	//}
	//m_map_Chunks.clear();
}
Mesh* DataContainer::GetMesh(std::string name)
{
	Mesh* mesh = m_map_Meshes[name];
	if (!mesh)
		DEFAULT_LOG("ERROR: Mesh not found of name: " + name);
	return mesh;
}

MeshBiomed * DataContainer::GetMeshBiomed(std::string name)
{
	return dynamic_cast<MeshBiomed*>(GetMesh(name));
}

AnimatedMesh* DataContainer::GetAnimation(std::string name)
{
	AnimatedMesh* mesh = m_map_Animated[name];
	if (!mesh)
		DEFAULT_LOG("ERROR: Animation not found of name: " + name);
	return new AnimatedMesh(*mesh);
}
GameObject* DataContainer::GetGameObject(std::string name)
{
	GameObject* go = m_map_GO[name];
	if (!go)
	{
		DEFAULT_LOG("ERROR: GameObject not found of name: " + name);
		return nullptr;
	}
	return go->Clone();
}
unsigned DataContainer::GetShader(std::string key)
{
	if (m_map_Shaders.count(key) <= 0)
		DEFAULT_LOG("ERROR: Shader not found of name: " + key);
	unsigned shader = m_map_Shaders[key];
	return shader;
}
ChunkData* DataContainer::GetChunk(std::string key)
{
	if (m_map_Chunks.count(key) <= 0)
	{
		DEFAULT_LOG("ERROR: Chunk not found of name: " + key);
		return nullptr;
	}
	return m_map_Chunks[key];
}
Behaviour * DataContainer::GetBehaviour(std::string key)
{
	if (m_map_Behaviour.count(key) <= 0)
		DEFAULT_LOG("ERROR: Behaviour not found of name: " + key);
	Behaviour* beheviour = new Behaviour(*m_map_Behaviour[key]);
	return beheviour;
}
unsigned DataContainer::GetTexture(std::string key)
{
	if (m_map_Textures.count(key) <= 0)
		DEFAULT_LOG("ERROR: Texture not found of name: " + key);
	unsigned tex = m_map_Textures[key];
	return tex;
}
HeightMapData* DataContainer::GetHeightMap(std::string key)
{
	if (m_map_HeightMaps.count(key) <= 0)
		DEFAULT_LOG("ERROR: Heightmap not found of name: " + key);
	return m_map_HeightMaps[key];
}
Mesh* DataContainer::GenerateTerrain(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrain(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}
MeshBiomed * DataContainer::GenerateTerrainBiomed(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrain(key, path, *heightMap, vScale, true);
	MeshBiomed* meshBiomed = dynamic_cast<MeshBiomed*>(mesh);

	m_map_HeightMaps[key] = new HeightMapData(meshBiomed, heightMap, vScale, vPos);
	return meshBiomed;
}
Mesh* DataContainer::GenerateTerrainTerrace(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrainTerrace(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}