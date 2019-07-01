#pragma once

#include "Mesh.h"
#include "MeshBuilder.h"
#include "Singleton.h"
#include <map>
#include <string>
#include "LoadTGA.h"
#include "MeshBuilder.h"
#include "GameObject.h"

class DataContainer : public Singleton<DataContainer>
{
private:
	std::map<std::string, Mesh*> m_map_Meshes;
	std::map<std::string, GameObject*> m_map_GO;
public:
	DataContainer();
	~DataContainer();

	Mesh* GetMesh(std::string name);
	GameObject* GetGameObject(std::string name);
};
