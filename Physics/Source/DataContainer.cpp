#include "DataContainer.h"

DataContainer::DataContainer()
{
	// Meshs--------------------------------------------------------------------------------
	m_map_Meshes["QUAD"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 5);
	//m_map_Meshes["CUBE"] = MeshBuilder::GenerateCube("CUBE", { 0,1,1 }, 10);
	m_map_Meshes["CUBE"] = MeshBuilder::GenerateOBJ("cubeobj", "Objects/cube.obj");
	m_map_Meshes["CUBE"]->m_uTextureArray[0] = LoadTGA("textures/cube.tga");
	m_map_Meshes["CUBE"]->m_uTextureArray[1] = LoadTGA("textures/moss1.tga");

	m_map_Meshes["GROUND"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 500);
	//m_map_Meshes["GROUND"]->m_uTextureArray[0] = 1;
	m_map_Meshes["DEPTH"] = MeshBuilder::GenerateQuad("DEPTH", { 1.f,1.f,1.f }, 10);
	m_map_Meshes["DEPTH"]->m_uTextureArray[0] = 1;

	std::vector<unsigned char> heightMap;
	m_map_Meshes["TERRAIN"] = MeshBuilder::GenerateTerrain("terrain", "data/heightMaps/heightmap.raw", heightMap);
	m_map_Meshes["TERRAIN"]->m_uTextureArray[0] = LoadTGA("textures/moss1.tga");

	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 52, 1000, 6, 6);
	m_map_Meshes["SkyPlane"]->m_uTextureArray[0] = LoadTGA("textures/sky.tga");

	m_map_Meshes["Animated"] = MeshBuilder::GenerateAnimatedMesh("Animated", 1, 6);
	m_map_Meshes["Animated"]->m_uTextureArray[0] = LoadTGA("textures/cat.tga");
	//--------------------------------------------------------------------------------
	// Gameobjects--------------------------------------------------------------------------------
	GameObject* cube = new GameObject();
	cube->GetComponent<TransformComponent>()->SetPosition(0, 10, 0);
	cube->GetComponent<TransformComponent>()->SetScale(10, 1, 10);
	cube->GetComponent<TransformComponent>()->SetRotation(90, 1, 0, 0);
	cube->AddComponent(new RenderComponent(this->GetMesh("CUBE")));
	cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	m_map_GO["CUBE"] = cube;
	//--------------------------------------------------------------------------------
	// Shaders--------------------------------------------------------------------------------
	m_map_Shaders["default"] = LoadShaders("Shader//Shadow/Shadow.vertexshader", "Shader//Shadow/Shadow.fragmentshader");
	m_map_Shaders["water"] = LoadShaders("Shader//water.vertexshader", "Shader//water.fragmentshader");
	m_map_Shaders["gpass"] = LoadShaders("Shader//shadow/GPass.vertexshader", "Shader//shadow/GPass.fragmentshader");
	//--------------------------------------------------------------------------------
}

DataContainer::~DataContainer()
{
	m_map_Meshes.clear();
}

Mesh* DataContainer::GetMesh(std::string name)
{
	Mesh* mesh = m_map_Meshes[name];
	if (!mesh)
		std::cout << "ERROR: Mesh not found of name: " << name << std::endl;
	return mesh;
}
GameObject* DataContainer::GetGameObject(std::string name)
{
	GameObject* go = m_map_GO[name];
	if (!go)
		std::cout << "ERROR: Mesh not found of name: " << name << std::endl;
	return go;
}
unsigned DataContainer::GetShader(std::string key)
{
	unsigned shader = -1;
	shader = m_map_Shaders[key];
	if (shader < 0)
		std::cout << "ERROR: Shader not found of name: " << key << std::endl;
	return shader;
}