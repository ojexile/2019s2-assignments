#include "RenderComponent.h"

RenderComponent::RenderComponent(Mesh* Mesh)
	:m_Mesh(Mesh)
{
	m_bLightEnabled = false;
	m_bBillboard = false;
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
	if (m_Mesh)
		this->m_Mesh->Update(dt);
	else
		DEFAULT_LOG("Mesh uninitialsed.");
}
void RenderComponent::SetBillboard(bool b)
{
	m_bBillboard = b;
}
bool RenderComponent::IsBillboard()
{
	return m_bBillboard;
}