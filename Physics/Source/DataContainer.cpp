#include "DataContainer.h"
#include "Rigidbody.h"

// Components================================================================================
#include "Constrain.h"
#include "MeshController.h"
// Scripts--------------------------------------------------------------------------------
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"

#include "FPSScript.h"

#include <time.h>
DataContainer::DataContainer()
{
	clock_t begin = clock();
	/// Meshes================================================================================
	// DO NOT REMOVE
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16);
	m_map_Meshes["Text"]->m_uTextureArray[0] = LoadTGA("calibri");
	//

	m_map_Meshes["ball"] = MeshBuilder::GenerateOBJ("ball");
	m_map_Meshes["ball"]->m_uTextureArray[0] = LoadTGA("ball");

	m_map_Meshes["sun"] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);

	m_map_Meshes["wall"] = MeshBuilder::GenerateCube("wall", Color((float)0.2, (float)0.2, (float)0.2), 1.f);

	m_map_Meshes["square"] = MeshBuilder::GenerateCube("wall", Color((float)0.5, (float)0.5, (float)0.2), 1.f);

	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 6, 400, 6, 6);
	m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("sky");

	m_map_Meshes["Particle"] = MeshBuilder::GenerateQuad("Particle", { 1.f,1.f,1.f }, 1);
	m_map_Meshes["Particle"]->m_uTextureArray[0] = LoadTGA("Particle");

	m_map_Animated["Leaf"] = MeshBuilder::GenerateAnimatedMesh("Leaf", 4, 4, 0, 15, 2.f, true);
	m_map_Animated["Leaf"]->m_Mesh->m_uTextureArray[0] = LoadTGA("Leaf2");

	m_map_Meshes["Tree"] = MeshBuilder::GenerateOBJ("treeShrunk");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("tree");
	m_map_Meshes["Tree"]->m_uTextureArray[0] = LoadTGA("moss1");

	/// Terrain================================================================================
	// Plains--------------------------------------------------------------------------------
	Mesh* mesh = GenerateTerrain("TerrainPlains", "heightmapPlains", { 200,60,200 }, { 0,0,0 });
	mesh->m_uTextureArray[0] = LoadTGA("dirt");
	mesh->m_uTextureArray[1] = LoadTGA("grassdirt");
	mesh->m_uTextureArray[2] = LoadTGA("grassdirt");
	/// Gameobjects================================================================================
	GameObject* go;

	// Generic Particle--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Particle"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Particle")));
	go->TRANS->SetScale(10, 10, 1);
	go->RENDER->SetLightEnabled(false);
	go->RENDER->SetColor({ 0,1,1 });
	ParticleScript* ps1 = new ParticleScript(1.5f, { 1.f,1.f,0 }, { 0,0,0 }, { 0,0,0 }, { -6.f,-6.f,0 }, { 1,1,0 }, { 0,0,0 }, { 0,0,0 });
	go->AddComponent(ps1);
	// Leaf--------------------------------------------------------------------------------
	GameObject* Leaf = new GameObject;
	m_map_GO["Leaf"] = Leaf;
	Leaf->AddComponent(new RenderComponent(this->GetAnimation("Leaf")));
	Leaf->GetComponent<RenderComponent>()->SetBillboard(true);
	float ampl = 0.1f;
	float freq = 0.8f;
	ParticleScript* ps = new ParticleScript(12.5f, { 0,-0.03f,0 }, { 0,0,0 }, { 0,-0.02f,0 }, { -0.01f,-0.01f,0 }, {}, { ampl,0,0 }, { freq,0,0 });
	//ps->SetCos({ 0,0,ampl }, { 0,0,freq });
	ps->SetRot({ 0,0,50 });
	Leaf->AddComponent(ps);
	// Leaf Spawner--------------------------------------------------------------------------------
	GameObject* LeafSpawner = new GameObject;
	m_map_GO["LeafSpawner"] = LeafSpawner;
	LeafSpawner->AddComponent(new ParticleSpawnerScript(GetGameObject("Leaf"), 1.5f, { 10,5,10 }, 1.f, "Default", -1.f));

	// ================================================================================
	/// Snow================================================================================
	// Rain--------------------------------------------------------------------------------
	GameObject* Snow = new GameObject;
	m_map_GO["Snow"] = Snow;
	Snow->AddComponent(new RenderComponent(this->GetMesh("Particle")));
	Snow->GetComponent<RenderComponent>()->SetBillboard(true);
	ParticleScript* snowps = new ParticleScript(25.0f, { 0,-.2f,0 }, { 0,0,0 }, { 0,0.001f,0 }, { -0.04f,-0.04f,0 }, {}, { 0.1f,0,0 }, { 1.1f,0,0 });
	snowps->SetCos({ 0,0, 0.1f }, { 0, 0,1.1f });
	Snow->AddComponent(snowps);
	Snow->RENDER->SetLightEnabled(false);
	// Rain Spawner--------------------------------------------------------------------------------
	GameObject* SnowSpawner = new GameObject;
	m_map_GO["SnowSpawner"] = SnowSpawner;
	SnowSpawner->AddComponent(new ParticleSpawnerScript(this->GetGameObject("Snow"), 0.2f, { 100,0,100 }, 0.8f, "Default", -1.f));
	// ================================================================================
	/// World================================================================================
	// tree--------------------------------------------------------------------------------
	go = new GameObject;
	m_map_GO["Tree"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("Tree")));
	go->AddComponent(new Rigidbody(Rigidbody::PILLAR, false));
	go->TRANS->SetScale(15, 100, 15);
	/// misc================================================================================
	go = new GameObject;
	m_map_GO["FPS"] = go;
	go->AddComponent(new FPSScript);
	go->TRANS->SetPosition(50, 10, 25);
	go->AddComponent(new RenderComponent(GetMesh("Text"), "0"));
	go->RENDER->SetColor({ 0.7f,1.7f,0.7f });
	m_map_Shaders["Default"] = LoadShaders("Flare", "Flare");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	//================================================================================
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	CHENG_LOG("Time to load container: ", std::to_string(elapsed_secs));
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
Mesh* DataContainer::GenerateTerrainTerrace(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrainTerrace(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}