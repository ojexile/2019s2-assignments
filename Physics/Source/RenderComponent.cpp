#include "RenderComponent.h"

RenderComponent::RenderComponent(Mesh* Mesh)
	:m_Mesh(Mesh)
{
	m_AnimatedMesh = nullptr;
	m_bLightEnabled = true;
	m_bBillboard = false;
	m_bIsText = false;
}
RenderComponent::RenderComponent(Mesh* Mesh, std::string sText)
	:m_Mesh(Mesh)
{
	m_sText = sText;
	m_AnimatedMesh = nullptr;
	m_bLightEnabled = false;
	m_bBillboard = false;
	m_bIsText = true;
}
RenderComponent::RenderComponent(AnimatedMesh* Mesh)
	: m_AnimatedMesh(Mesh)
{
	m_Mesh = nullptr;
	m_bLightEnabled = false;	// Transparency doesn't work with light enabled
	m_bBillboard = false;
	m_bIsText = false;
}
RenderComponent::RenderComponent(RenderComponent& ref)
{
	if (ref.m_Mesh)
		m_Mesh = ref.m_Mesh;
	else
		m_Mesh = nullptr;
	if (ref.m_AnimatedMesh)
		m_AnimatedMesh = new AnimatedMesh(*ref.m_AnimatedMesh);
	else
		m_AnimatedMesh = nullptr;
	m_bLightEnabled = ref.m_bLightEnabled;
	m_bBillboard = ref.m_bBillboard;
	m_bIsText = ref.m_bIsText;
	m_sText = ref.m_sText;
}

RenderComponent::~RenderComponent()
{
	if (m_AnimatedMesh)
		delete m_AnimatedMesh;
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
		m_Material.kAmbient.Set(color.x, color.y, color.z);
	}
}
void RenderComponent::ResetColor(Vector3 color)
{
	if (m_Mesh)
	{
		m_Material.Reset();
	}
}
Material RenderComponent::GetMaterial()
{
	return m_Material;
}
void RenderComponent::SetMesh(Mesh* mesh)
{
	m_Mesh = mesh;
}
void RenderComponent::SetMesh(AnimatedMesh* mesh)
{
	m_AnimatedMesh = mesh;
}
bool RenderComponent::IsText()
{
	return m_bIsText;
}
std::string RenderComponent::GetText()
{
	return m_sText;
}
void RenderComponent::SetText(std::string s)
{
	m_sText = s;
}