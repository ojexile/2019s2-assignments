#include "DataContainer.h"
#include "Resources.h"
#include <time.h>
DataContainer::DataContainer()
{
	clock_t begin = clock();
	// Meshs--------------------------------------------------------------------------------
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16);
	m_map_Meshes["Text"]->m_uTextureArray[0] = LoadTGA("calibri");
	//m_map_Meshes["Text"]->material.kAmbient.Set(1, 0, 0);

	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuad("Quad", { 1,1,1 }, 5);
	//m_map_Meshes["CUBE"] = MeshBuilder::GenerateCube("CUBE", { 0,1,1 }, 10);
	m_map_Meshes["Cube"] = MeshBuilder::GenerateOBJ("cube");
	m_map_Meshes["Cube"]->m_uTextureArray[0] = LoadTGA("cube");
	m_map_Meshes["Cube"]->m_uTextureArray[1] = LoadTGA("moss1");

	m_map_Meshes["Ground"] = MeshBuilder::GenerateQuad("Ground", { 1.f,1.f,1.f }, 500);
	//m_map_Meshes["GROUND"]->m_uTextureArray[0] = 1;
	m_map_Meshes["Depth"] = MeshBuilder::GenerateQuad("Depth", { 1.f,1.f,1.f }, 10);
	m_map_Meshes["Depth"]->m_uTextureArray[0] = 1;

	_heightmap* heightMap = new _heightmap;
	m_map_HeightMaps["Terrain"] = heightMap;
	m_map_Meshes["Terrain"] = MeshBuilder::GenerateTerrain("terrain", "heightmapMain", *heightMap, { 500,30,500 });
	m_map_Meshes["Terrain"]->m_uTextureArray[0] = LoadTGA("moss1");

	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 52, 1000, 6, 6);
	m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("sky");

	m_map_Animated["Cat"] = MeshBuilder::GenerateAnimatedMesh("Animated", 1, 6, 0, 5, 1.f, true);
	m_map_Animated["Cat"]->m_Mesh->m_uTextureArray[0] = LoadTGA("cat");

	m_map_Meshes["Water"] = MeshBuilder::GenerateOBJ("water");
	m_map_Meshes["Water"]->m_uTextureArray[0] = LoadTGA("water");
	//--------------------------------------------------------------------------------
	// Gameobjects--------------------------------------------------------------------------------
	GameObject* cube = new GameObject();
	cube->GetComponent<TransformComponent>()->SetPosition(0, 10, 0);
	cube->GetComponent<TransformComponent>()->SetScale(10, 1, 10);
	cube->GetComponent<TransformComponent>()->SetRotation(45, 0, 1, 0);
	cube->AddComponent(new RenderComponent(this->GetMesh("Cube")));
	cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	cube->RENDER->SetBillboard(true);
	m_map_GO["Cube"] = cube;
	//--------------------------------------------------------------------------------
	// Shaders--------------------------------------------------------------------------------
	m_map_Shaders["Default"] = LoadShaders("Shadow", "Shadow");
	m_map_Shaders["Water"] = LoadShaders("water", "water");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	//--------------------------------------------------------------------------------

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	DEFAULT_LOG("Time to load datacontainer: " + std::to_string(elapsed_secs));
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
	return mesh;
}
GameObject* DataContainer::GetGameObject(std::string name)
{
	GameObject* go = m_map_GO[name];
	if (!go)
		DEFAULT_LOG("ERROR: GameObject not found of name: " + name);
	return go;
}
unsigned DataContainer::GetShader(std::string key)
{
	if (m_map_Shaders.count(key) <= 0)
		DEFAULT_LOG("ERROR: Shader not found of name: " + key);
	unsigned shader = m_map_Shaders[key];
	return shader;
}
_heightmap* DataContainer::GetHeightMap(std::string key)
{
	if (m_map_HeightMaps.count(key) <= 0)
		DEFAULT_LOG("ERROR: Heightmap not found of name: " + key);
	return m_map_HeightMaps[key];
}