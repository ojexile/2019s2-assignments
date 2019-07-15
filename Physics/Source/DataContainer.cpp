#include "DataContainer.h"
#include "Resources.h"
DataContainer::DataContainer()
{
	//// Meshs--------------------------------------------------------------------------------
	//m_map_Meshes["Quad"] = MeshBuilder::GenerateQuad("Quad", { 1,1,1 }, 5);
	////m_map_Meshes["CUBE"] = MeshBuilder::GenerateCube("CUBE", { 0,1,1 }, 10);
	//m_map_Meshes["Cube"] = MeshBuilder::GenerateOBJ("cubeobj", "cube");
	//m_map_Meshes["Cube"]->m_uTextureArray[0] = LoadTGA("cube");
	//m_map_Meshes["Cube"]->m_uTextureArray[1] = LoadTGA("moss1");

	//m_map_Meshes["Ground"] = MeshBuilder::GenerateQuad("Ground", { 1.f,1.f,1.f }, 500);
	////m_map_Meshes["GROUND"]->m_uTextureArray[0] = 1;
	//m_map_Meshes["Depth"] = MeshBuilder::GenerateQuad("Depth", { 1.f,1.f,1.f }, 10);
	//m_map_Meshes["Depth"]->m_uTextureArray[0] = 1;

	//std::vector<unsigned char> heightMap;
	//m_map_Meshes["Terrain"] = MeshBuilder::GenerateTerrain("terrain", "heightmapMain", heightMap);
	//m_map_Meshes["Terrain"]->m_uTextureArray[0] = LoadTGA("moss1");

	//m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 52, 1000, 6, 6);
	//m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("sky");

	//m_map_Animated["Cat"] = MeshBuilder::GenerateAnimatedMesh("Animated", 1, 6, 0, 5, 1.f, true);
	//m_map_Animated["Cat"]->m_Mesh->m_uTextureArray[0] = LoadTGA("cat");

	//m_map_Meshes["Water"] = MeshBuilder::GenerateOBJ("cubeobj", "water");
	//m_map_Meshes["Water"]->m_uTextureArray[0] = LoadTGA("water");
	////--------------------------------------------------------------------------------
	//// Gameobjects--------------------------------------------------------------------------------
	//GameObject* cube = new GameObject();
	//cube->GetComponent<TransformComponent>()->SetPosition(0, 10, 0);
	//cube->GetComponent<TransformComponent>()->SetScale(10, 1, 10);
	//cube->GetComponent<TransformComponent>()->SetRotation(45, 0, 1, 0);
	//cube->AddComponent(new RenderComponent(this->GetMesh("Cube")));
	//cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	//cube->GetComponent<RenderComponent>()->SetBillboard(true);
	//m_map_GO["Cube"] = cube;
	//--------------------------------------------------------------------------------
	// Shaders--------------------------------------------------------------------------------
	m_map_Shaders["Default"] = LoadShaders("Shadow", "Shadow");
	m_map_Shaders["Water"] = LoadShaders("water", "water");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	//--------------------------------------------------------------------------------
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