#pragma once
#include "Component.h"
#include "Mesh.h"
#include "MeshBiomed.h"
#include "AnimatedMesh.h"
#include <string>

class RenderComponent :
	public Component
{
private:
	Mesh* m_Mesh;
	MeshBiomed* m_MeshBiomed;
	AnimatedMesh* m_AnimatedMesh;
	bool m_bLightEnabled;
	bool m_bBillboard;
	bool m_b3DBillboard;
	float m_fRenderDistance;
	Material m_Material;
	std::string m_sText;
	bool m_bIsText;
	bool m_bTextOnScreen;
public:
	RenderComponent();
	RenderComponent(Mesh* mesh);
	RenderComponent(MeshBiomed* mesh);
	RenderComponent(Mesh* mesh, std::string sText, bool onScreen = true);
	RenderComponent(AnimatedMesh* mesh);
	RenderComponent(RenderComponent& mesh);

	float GetRenderDistance();
	void SetRenderDistance(float);

	virtual ~RenderComponent();
	virtual Component* Clone()
	{
		return new RenderComponent(*this);
	};

	Mesh* GetMesh();
	MeshBiomed* GetMeshBiomed();
	AnimatedMesh* GetAnimatedMesh();

	bool GetLightEnabled();
	void SetLightEnabled(bool b);
	void SetBillboard(bool b);
	void Set3DBillboard(bool b);
	bool IsBillboard();
	bool Is3DBillboard();
	void SetColor(Vector3 color);
	void SetColor(float x, float y, float z);
	void SetColor(float x);
	void ResetColor();
	Material GetMaterial();
	void Update(double dt) override;
	void SetMesh(Mesh* mesh);
	void SetMesh(AnimatedMesh* mesh);
	bool IsText();
	bool IsTextOnScreen();
	std::string GetText();
	void SetText(std::string);
	void AddText(std::string);
	void AddText(char c);
	void RemoveText();
	void DeleteMeshBiomed();

	void SetAlpha(float a);
};
