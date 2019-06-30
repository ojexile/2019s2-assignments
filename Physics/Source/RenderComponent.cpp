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
void RenderComponent::SetLightEnabled(bool b)
{
	m_bLightEnabled = b;
}
void RenderComponent::Update(double dt)
{
}