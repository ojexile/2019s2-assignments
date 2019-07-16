#include "RenderComponent.h"

RenderComponent::RenderComponent(Mesh* Mesh)
	:m_Mesh(Mesh)
{
	m_AnimatedMesh = nullptr;
	m_bLightEnabled = true;
	m_bBillboard = false;
	if (!Mesh)
		DEFAULT_LOG("Mesh is null.");

}
RenderComponent::RenderComponent(AnimatedMesh* Mesh)
	: m_AnimatedMesh(Mesh)
{
	m_Mesh = nullptr;
	m_bLightEnabled = false;
	m_bBillboard = false;
	if (!Mesh)
		DEFAULT_LOG("Mesh is null.");
}
RenderComponent::RenderComponent(RenderComponent& ref)
{
	if (ref.m_Mesh)
		m_Mesh = ref.m_Mesh;
	else
		m_Mesh = nullptr;
	if (ref.m_AnimatedMesh)
		m_AnimatedMesh = ref.m_AnimatedMesh;
	else
		m_AnimatedMesh = nullptr;
	m_bLightEnabled = ref.m_bLightEnabled;
	m_bBillboard = ref.m_bBillboard;
}

RenderComponent::~RenderComponent()
{
}

Mesh* RenderComponent::GetMesh()
{
	return m_Mesh;
}

AnimatedMesh* RenderComponent::GetAnimatedMesh()
{
	return m_AnimatedMesh;
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
	if (m_AnimatedMesh)
		this->m_AnimatedMesh->Update(dt);
}
void RenderComponent::SetBillboard(bool b)
{
	m_bBillboard = b;
}
bool RenderComponent::IsBillboard()
{
	return m_bBillboard;
}
void RenderComponent::SetColor(Vector3 color)
{
	if (m_Mesh)
	{
		m_Mesh->material.kAmbient.Set(color.x, color.y, color.z);
	}
}