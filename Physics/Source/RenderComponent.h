#pragma once
#include "ComponentBase.h"
#include "Mesh.h"
#include "AnimatedMesh.h"
#include "MeshBiomed.h"
#include <string>

class RenderComponent :
	public ComponentBase
{
private:
	Mesh* m_Mesh;
	AnimatedMesh* m_AnimatedMesh;
	bool m_bLightEnabled;
	bool m_bBillboard;
	Material m_Material;
	std::string m_sText;
	bool m_bIsText;
public:
	RenderComponent(Mesh* mesh);
	RenderComponent(MeshBiomed*, BiomeComponent*);
	RenderComponent(Mesh* mesh, std::string sText);
	RenderComponent(AnimatedMesh* mesh);
	RenderComponent(RenderComponent& mesh);

	virtual ~RenderComponent();
	virtual ComponentBase* Clone()
	{
		return new RenderComponent(*this);
	};

	Mesh* GetMesh();
	AnimatedMesh* GetAnimatedMesh();
	bool GetLightEnabled();
	void SetLightEnabled(bool b);
	void SetBillboard(bool b);
	bool IsBillboard();
	void SetColor(Vector3 color);
	void ResetColor(Vector3 color);
	Material GetMaterial();
	void Update(double dt) override;
	void SetMesh(Mesh* mesh);
	void SetMesh(AnimatedMesh* mesh);
	bool IsText();
	std::string GetText();
	void SetText(std::string);
};
