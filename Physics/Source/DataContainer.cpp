#include "DataContainer.h"
#include "ChengRigidbody.h"
#include "BallScript.h"
DataContainer::DataContainer()
{
	// Meshes================================================================================
	m_map_Meshes["ground"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 500);
	m_map_Meshes["ball"] = MeshBuilder::GenerateSphere("ball", Color(1, 0, 0), 10, 10, 1.f);
	m_map_Meshes["ball2"] = MeshBuilder::GenerateSphere("ball", Color(0, 0, 1), 10, 10, 1.f);
	m_map_Meshes["ball3"] = MeshBuilder::GenerateSphere("ball", Color(0, 1, 0), 10, 10, 1.f);
	m_map_Meshes["pillar"] = MeshBuilder::GenerateOBJ("pillar", "cylinder");
	m_map_Meshes["wall"] = MeshBuilder::GenerateCube("wall", Color((float)0.2, (float)0.2, (float)0.2), 1.f);
	m_map_Meshes["square"] = MeshBuilder::GenerateCube("wall", Color((float)0.5, (float)0.5, (float)0.5), 1.f);
	m_map_Meshes["ceil"] = MeshBuilder::GenerateCube("wall", Color((float)0.9, (float)0.9, (float)0.9), 1.f);
	m_map_Meshes["floor"] = MeshBuilder::GenerateCube("wall", Color((float)0.8, (float)0.8, (float)0.8), 1.f);
	//m_map_Meshes["GROUND"]->m_uTextureArray[0] = 1;

	//--------------------------------------------------------------------------------
	// Gameobjects================================================================================
	GameObject* ball = new GameObject;
	m_map_GO["ball"] = ball;
	ball->AddComponent(new RenderComponent(this->GetMesh("ball")));
	ball->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	ball->AddComponent(new BallScript());
	// --------------------------------------------------------------------------------
	GameObject * ball2 = new GameObject;
	m_map_GO["ball2"] = ball2;
	ball2->AddComponent(new RenderComponent(this->GetMesh("ball2")));
	ball2->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	// --------------------------------------------------------------------------------
	GameObject* go = new GameObject;
	m_map_GO["ball3"] = go;
	go->AddComponent(new RenderComponent(this->GetMesh("ball3")));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	// --------------------------------------------------------------------------------
	GameObject* wall = new GameObject;
	m_map_GO["wall"] = wall;

	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("wall")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL));
	// --------------------------------------------------------------------------------
	wall = new GameObject;
	m_map_GO["ceil"] = wall;

	wall->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	wall->AddComponent(new RenderComponent(this->GetMesh("ceil")));
	wall->AddComponent(new ChengRigidbody(ChengRigidbody::WALL));
	// --------------------------------------------------------------------------------
	GameObject* square = new GameObject;
	m_map_GO["square"] = square;

	square->AddComponent(new RenderComponent(this->GetMesh("square")));
	square->AddComponent(new ChengRigidbody(ChengRigidbody::SQUARE));
	// --------------------------------------------------------------------------------
	GameObject* floor = new GameObject;
	m_map_GO["floor"] = floor;

	floor->GetComponent<TransformComponent>()->SetRotation(-90, 0, 1, 0);
	floor->AddComponent(new RenderComponent(this->GetMesh("floor")));
	floor->AddComponent(new ChengRigidbody(ChengRigidbody::BOX));
	//--------------------------------------------------------------------------------
	GameObject* pillar = new GameObject;
	m_map_GO["pillar"] = pillar;
	pillar->AddComponent(new RenderComponent(this->GetMesh("pillar")));
	pillar->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR));
	//wall->GetComponent<ChengRigidbody>()->SetNormal({ 0, 0, -1 });
	// Shaders================================================================================
	m_map_Shaders["Default"] = LoadShaders("Shadow", "Shadow");

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