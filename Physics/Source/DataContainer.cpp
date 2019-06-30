#include "DataContainer.h"

DataContainer::DataContainer()
{
	m_map_Meshes["QUAD"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 5);
	//m_map_Meshes["CUBE"] = MeshBuilder::GenerateCube("CUBE", { 0,1,1 }, 10);
	m_map_Meshes["CUBE"] = MeshBuilder::GenerateOBJ("cubeobj", "Objects/cube.obj");
	m_map_Meshes["CUBE"]->m_uTextureArray[0] = LoadTGA("textures/cube.tga");
	m_map_Meshes["CUBE"]->m_uTextureArray[1] = LoadTGA("textures/moss1.tga");

	m_map_Meshes["GROUND"] = MeshBuilder::GenerateQuad("ground", { 1.f,1.f,1.f }, 15);
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