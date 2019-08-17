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
#include "WeaponScript.h"
#include "GrenadeScript.h"
#include "LootScript.h"
#include "DestructibleEntityScript.h"
//
#include "PartScript.h"
#include "WeaponPartScript.h"
#include <time.h>
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

	InitTextures();
	InitMeshes();
	InitTerrain();
	InitGO();
	InitChunks();
	InitShaders();
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
	m_map_Textures["Ball"] = LoadTGA("Ball");

	m_map_Textures["Revolver"] = LoadTGA("revolver");
	m_map_Textures["InventorySlot"] = LoadTGA("inventorySlot");

	m_map_Textures["plaintree"] = LoadTGA("plain_tree");
	m_map_Textures["snowtree"] = LoadTGA("snow_tree");
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

	m_map_Meshes["Muzzle"] = MeshBuilder::GenerateOBJ("Muzzle")->AddTexture("Ball");

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

	m_map_Meshes["Revolver"] = MeshBuilder::GenerateOBJ("revolver")->AddTexture("Revolver");

	m_map_Meshes["Grenade"] = MeshBuilder::GenerateOBJ("Ball")->AddTexture("InventorySlot");

	m_map_Meshes["UIButton"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("InventorySlot");

	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuadLeftCentered({}, 1);

	m_map_Meshes["particlequad"] = MeshBuilder::GenerateQuad("particlequad", { 1,1,1 }, 1.f);
}
void  DataContainer::InitTerrain()
{
	/// Terrain================================================================================
	// Plains--------------------------------------------------------------------------------
	MeshBiomed* mesh1 = GenerateTerrainBiomed("TerrainPlains", "heightmapPlains", { 200,60,200 }, { 0,0,0 })
		->AddTexture("Cube", BiomeComponent::BIOME_PLAINS);
		//->AddTexture(("grassdirt"), BiomeComponent::BIOME_FLAT);
}
void  DataContainer::InitGO()
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
	go->RIGID->SetMass(0.01f);
	go->RIGID->SetMat(1, 1);
	go->AddComponent(new ProjectileScript(1.0, 100.0));
	/// Weapon Parts================================================================================
	go = new GameObject();
	m_map_GO["Muzzle"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Muzzle")));
	go->AddComponent(new WeaponPartScript(PartScript::MUZZLE, 0.5, 1));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->RIGID->SetResponseActive(false);
	go = new GameObject();
	m_map_GO["Clip"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Clip")));
	go->AddComponent(new WeaponPartScript(PartScript::CLIP, 2.0, 50));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetResponseActive(false);
	go = new GameObject();
	m_map_GO["Scope"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Scope")));
	go->AddComponent(new WeaponPartScript(PartScript::SCOPE, 0.5, 1));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetResponseActive(false);
	go = new GameObject();
	m_map_GO["Grip"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Grip")));
	go->AddComponent(new WeaponPartScript(PartScript::GRIP, 2.0, 50));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetResponseActive(false);
	// Gun--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Gun"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Revolver")));
	go->AddComponent(new WeaponScript(GetGameObject("Bullet")));
	// Grenade----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Grenade"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->TRANS->SetScale(0.5);
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	go->RIGID->SetMass(0.25f);
	go->RIGID->SetMat(0.9f, 0.f);
	go->AddComponent(new GrenadeScript(3.0, 10.0, 2));
	// Loot------------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Loot"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	//go->RENDER->SetActive(false);
	//Enemies-----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["BaseEnemy"] = go;
	go->TRANS->SetScale(1.f);
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetMat(0.9f, 0);
	go->AddComponent(new EntityScript());
	go->AddComponent(new LootScript());
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["FPS"] = go;
	go->AddComponent(new FPSScript);
	go->TRANS->SetPosition(50, 10, 25);
	go->AddComponent(new RenderComponent(GetMesh("Text"), "0"));
	go->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	// InventorySlot--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["InventorySlot"] = go;
	go->AddComponent(new UIButtonComponent);
	go->AddComponent(new RenderComponent(GetMesh("UIButton")));
	go->RENDER->SetLightEnabled(false);
	go->TRANS->SetScale(100);
	// CustomiseSlot--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["CustomiseSlot"] = go;
	go->AddComponent(new UIButtonComponent);
	go->AddComponent(new RenderComponent(GetMesh("UIButton")));
	go->RENDER->SetLightEnabled(false);
	go->TRANS->SetScale(100);
	// BulletUI--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["BulletUI"] = go;
	go->AddComponent(new UIButtonComponent);
	go->AddComponent(new RenderComponent(GetMesh("UIButton")));
	go->RENDER->SetLightEnabled(false);
	go->TRANS->SetScale(50, 20, 1);

	// Interactabes--------------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["particledestroy"] = go;
	go->AddComponent(new RenderComponent(GetMesh("particlequad")));
	go->GetComponent<RenderComponent>()->SetColor(1.f , 0.6f, 0.2f);
	go->GetComponent<RenderComponent>()->SetBillboard(true);
	go->AddComponent(new ParticleScript(1.f, Vector3(0.f, 1.f, 0.f), Vector3(0.f, 100.f, 0.f), Vector3(), Vector3(), Vector3(1.f, 1.f, 1.f)));

	go = new GameObject();
	m_map_GO["particlespawnerdestroy"] = go;
	go->AddComponent(new ParticleSpawnerScript(m_map_GO["particledestroy"], 100, Vector3(), 0.f, "Default", 10.f));

	go = new GameObject();
	m_map_GO["plaintree"] = go;
	go->AddComponent(new RenderComponent(GetMeshBiomed("plaintree")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetMat(0.9f, 0);
	go->AddComponent(new DestructibleEntityScript(m_map_GO["particlespawnerdestroy"]));
}
void  DataContainer::InitShaders()
{
	m_map_Shaders["Default"] = LoadShaders("Flare", "Flare");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
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