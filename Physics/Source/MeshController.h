#pragma once
#include "ComponentBase.h"
#include <map>
#include <string>
#include "RenderComponent.h"
#include "Mesh.h"
#include "AnimatedMesh.h"
template<class t>
class MeshController : public ComponentBase
{
private:
	std::map<std::string, t*> m_map_List;
public:
	MeshController();
	virtual ~MeshController();
	virtual ComponentBase* Clone()
	{
		return new MeshController(*this);
	};
	void AddMesh(std::string name, t* mesh);
	void SetMesh(std::string s);
};

MeshController<Mesh> mesh; 
MeshController<AnimatedMesh> amesh;