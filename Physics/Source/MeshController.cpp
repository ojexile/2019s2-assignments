#include "MeshController.h"


template<class t>
MeshController<t>::MeshController()
{
}

template<class t>
MeshController<t>::~MeshController()
{
}
template<class t>
void MeshController<t>::AddMesh(std::string name, t* mesh)
{
	m_map_List[name] = mesh;
}
template<class t>
void MeshController<t>::SetMesh(std::string s)
{
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
}