#pragma once
#include "ComponentBase.h"
#include <map>
#include <string>
#include "RenderComponent.h"
#include "Mesh.h"
#include "AnimatedMesh.h"
template<class t>
class MeshController : public Component
{
private:
	std::map<std::string, t*> m_map_List;
public:
	MeshController() {};
	virtual ~MeshController() {};
	virtual Component* Clone()
	{
		return new MeshController(*this);
	};
	void AddMesh(std::string name, t* mesh)
	{
		m_map_List[name] = mesh;
	};
	void SetMesh(std::string s) {
		RenderComponent* rc = GetComponent<RenderComponent>();
		if (!rc)
		{
			DEFAULT_LOG("No render component tied with mesh controller.");
			return;
		}
		if (m_map_List.count(s) <= 0)
		{
			DEFAULT_LOG("Unknown mesh of name: " + s);
			return;
		}
		rc->SetMesh(m_map_List[s]);
	};
	virtual void Update(double dt) override
	{
	};
};
