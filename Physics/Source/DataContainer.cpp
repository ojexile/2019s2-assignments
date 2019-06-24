#include "DataContainer.h"

DataContainer::DataContainer()
{
	m_map_Meshes["QUAD"] = MeshBuilder::GenerateQuad("QUAD", { 1,1,1 }, 5);
	m_map_Meshes["CUBE"] = MeshBuilder::GenerateCube("CUBE", { 0,1,1 }, 10);
}

DataContainer::~DataContainer()
{
	delete TestMesh;
}

Mesh* DataContainer::GetMesh(std::string name)
{
	return m_map_Meshes[name];
}