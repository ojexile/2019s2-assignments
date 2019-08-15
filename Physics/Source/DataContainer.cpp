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
	CHENG_LOG("Time to load container: ", std::to_string(elapsed_secs));
}

void DataContainer::InitChunks()
{
	m_map_Chunks["Map"] = new ChunkData("Content/Map.chunk");
	m_map_Chunks["goldmine"] = new ChunkData("Content/1x2_goldmine.chunk");
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

	m_map_Textures["Revolver"] = LoadTGA("revolver");
	m_map_Textures["InventorySlot"] = LoadTGA("inventorySlot");
}
void  DataContainer::InitMeshes()
{
	/// Meshes================================================================================
	/// DO NOT REMOVE--------------------------------------------------------------------------------
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16)->AddTexture("Text");
	//--------------------------------------------------------------------------------
	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 6, 400, 6, 6)->AddTexture("Sky");
	m_map_Meshes["Axis"] = MeshBuilder::GenerateAxes("Axes", 10, 10, 10);

	m_map_Meshes["Cube"] = MeshBuilder::GenerateOBJ("Cube")->AddTexture("Cube");

	m_map_Meshes["Ball"] = MeshBuilder::GenerateOBJ("Ball")->AddTexture("Cube");

	m_map_Meshes["Player"] = MeshBuilder::GenerateOBJ("Player")->AddTexture("Cube");

	m_map_Meshes["Reticle"] = MeshBuilder::GenerateOBJ("Reticle");

	m_map_Meshes["Revolver"] = MeshBuilder::GenerateOBJ("revolver")->AddTexture("Revolver");

	m_map_Meshes["UIButton"] = MeshBuilder::GenerateQuad("", {}, 1)->AddTexture("InventorySlot");

	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuadLeftCentered({}, 1);
}
void  DataContainer::InitTerrain()
{
	/// Terrain================================================================================
	// Plains--------------------------------------------------------------------------------
}
void  DataContainer::InitGO()
{
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	///================================================================================
	// Reticle--------------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["Reticle"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Reticle")));
	go->RENDER->SetColor(0, 1, 1);
	go->AddComponent(new ReticleScript);
	//Bullet--------------------------------------------------------------------------------
	go = new GameObject();
	m_map_GO["Bullet"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->RIGID->SetMass(0.01f);
	go->AddComponent(new ProjectileScript(1.0, 50.0));
	/// Weapon Parts================================================================================
	go = new GameObject();
	m_map_GO["Muzzle"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new WeaponPartScript(PartScript::MUZZLE, 0.5, 1));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	go->RIGID->SetResponseActive(false);
	// Gun--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Gun"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Revolver")));
	go->AddComponent(new WeaponScript(GetGameObject("Bullet")));
	//Enemies-----------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["BaseEnemy"] = go;
	go->TRANS->SetScale(0.5f);
	go->AddComponent(new RenderComponent(GetMesh("Ball")));
	go->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	go->AddComponent(new EntityScript());
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