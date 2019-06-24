#include "RenderComponent.h"



RenderComponent::RenderComponent(Mesh* Mesh)
	:m_Mesh(Mesh)
{
	m_bLightEnabled = false;
}


RenderComponent::~RenderComponent()
{
}

Mesh* RenderComponent::GetMesh()
{
	return m_Mesh;
}

bool RenderComponent::GetLightEnabled()
{
	return m_bLightEnabled;
}