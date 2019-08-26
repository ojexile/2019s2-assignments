#include "RenderComponent.h"

RenderComponent::RenderComponent()
{
	m_Mesh = nullptr;
	m_fRenderDistance = 3000;
	m_AnimatedMesh = nullptr;
	m_MeshBiomed = nullptr;
	m_bLightEnabled = true;
	m_bBillboard = false;
	m_b3DBillboard = false;
	m_bIsText = false;
	m_bTextOnScreen = false;
}

RenderComponent::RenderComponent(Mesh* Mesh)
	:m_Mesh(Mesh)
{
	m_fRenderDistance = -1;
	m_AnimatedMesh = nullptr;
	m_MeshBiomed = nullptr;
	m_bLightEnabled = true;
	m_bBillboard = false;
	m_b3DBillboard = false;
	m_bIsText = false;
	m_bTextOnScreen = false;
}
RenderComponent::RenderComponent(MeshBiomed * meshBiomed)
	:m_MeshBiomed(meshBiomed)
{
	m_fRenderDistance = 400;
	m_Mesh = nullptr;
	m_AnimatedMesh = nullptr;
	m_bLightEnabled = true;
	m_bBillboard = false;
	m_b3DBillboard = false;
	m_bIsText = false;
	m_bTextOnScreen = false;
}
RenderComponent::RenderComponent(Mesh* Mesh, std::string sText, bool OnScreen)
	:m_Mesh(Mesh)
{
	m_fRenderDistance = -1;
	m_sText = sText;
	m_AnimatedMesh = nullptr;
	m_MeshBiomed = nullptr;
	m_bLightEnabled = false;
	m_bBillboard = false;
	m_b3DBillboard = false;
	m_bIsText = true;
	m_bTextOnScreen = OnScreen;
	if (!OnScreen)
		m_b3DBillboard = true;
}
RenderComponent::RenderComponent(AnimatedMesh* Mesh)
	: m_AnimatedMesh(Mesh)
{
	m_fRenderDistance = 400;
	m_Mesh = nullptr;
	m_MeshBiomed = nullptr;

	m_bLightEnabled = false;	// Transparency doesn't work with light enabled
	m_bBillboard = false;
	m_b3DBillboard = false;
	m_bIsText = false;
	m_bTextOnScreen = false;
}
RenderComponent::RenderComponent(RenderComponent& ref)
{
	m_fRenderDistance = ref.m_fRenderDistance;
	if (ref.m_Mesh)
		m_Mesh = ref.m_Mesh;
	else
		m_Mesh = nullptr;
	if (ref.m_AnimatedMesh)
		m_AnimatedMesh = new AnimatedMesh(*ref.m_AnimatedMesh);
	else
		m_AnimatedMesh = nullptr;

	if (ref.m_MeshBiomed)
		m_MeshBiomed = ref.m_MeshBiomed;
	else
		m_MeshBiomed = nullptr;

	m_bLightEnabled = ref.m_bLightEnabled;
	m_bBillboard = ref.m_bBillboard;
	m_bIsText = ref.m_bIsText;
	m_sText = ref.m_sText;
	m_b3DBillboard = ref.m_b3DBillboard;
	m_Material = ref.m_Material;
	m_bTextOnScreen = ref.m_bTextOnScreen;
}

float RenderComponent::GetRenderDistance()
{
	return m_fRenderDistance;
}

void RenderComponent::SetRenderDistance(float k)
{
	m_fRenderDistance = k;
}

RenderComponent::~RenderComponent()
{
	if (m_AnimatedMesh)
		delete m_AnimatedMesh;
	if (m_MeshBiomed)
		delete m_MeshBiomed;
}

Mesh* RenderComponent::GetMesh()
{
	return m_Mesh;
}

MeshBiomed * RenderComponent::GetMeshBiomed()
{
	return m_MeshBiomed;
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
void RenderComponent::Set3DBillboard(bool b)
{
	m_b3DBillboard = b;
}
bool RenderComponent::Is3DBillboard()
{
	return m_b3DBillboard;
}
void RenderComponent::SetColor(Vector3 color)
{
	m_Material.kAmbient.Set(color.x, color.y, color.z);
	m_Material.kDiffuse.Set(color.x, color.y, color.z);
}
void RenderComponent::SetColor(float x, float y, float z)
{
	m_Material.kAmbient.Set(x, y, z);
	m_Material.kDiffuse.Set(x, y, z);
}
void RenderComponent::SetColor(float x)
{
	m_Material.kAmbient.Set(x, x, x);
	m_Material.kDiffuse.Set(x, x, x);
}
void RenderComponent::ResetColor()
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
void RenderComponent::DeleteMeshBiomed()
{
	delete m_MeshBiomed;
}
void RenderComponent::SetAlpha(float a)
{
	m_Material.kAlpha = a;
}
bool RenderComponent::IsTextOnScreen()
{
	return m_bTextOnScreen;
}