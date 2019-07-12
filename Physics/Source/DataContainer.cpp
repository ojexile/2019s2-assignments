#include "DataContainer.h"

DataContainer::DataContainer()
{
	// Meshs--------------------------------------------------------------------------------

	m_map_Meshes["Ground"] = MeshBuilder::GenerateQuad("Ground", { 1.f,1.f,1.f }, 500);
	//m_map_Meshes["GROUND"]->m_uTextureArray[0] = 1;

	//--------------------------------------------------------------------------------
	// Gameobjects--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	// Shaders--------------------------------------------------------------------------------
	m_map_Shaders["Default"] = LoadShaders("Shader//Shadow/Shadow.vertexshader", "Shader//Shadow/Shadow.fragmentshader");

	m_map_Shaders["GPass"] = LoadShaders("Shader//shadow/GPass.vertexshader", "Shader//shadow/GPass.fragmentshader");
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