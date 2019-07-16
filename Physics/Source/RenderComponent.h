#pragma once
#include "ComponentBase.h"
#include "Mesh.h"
#include "AnimatedMesh.h"

class RenderComponent :
	public ComponentBase
{
private:
	Mesh* m_Mesh;
	AnimatedMesh* m_AnimatedMesh;
	bool m_bLightEnabled;
	bool m_bBillboard;
	Material m_Material;
public:
	RenderComponent(Mesh* mesh);
	RenderComponent(AnimatedMesh* mesh);
	RenderComponent(RenderComponent&);
	virtual ~RenderComponent();
	virtual ComponentBase* Clone()
	{
		return new RenderComponent(*this);
	}

	Mesh* GetMesh();
	AnimatedMesh* GetAnimatedMesh();
	bool GetLightEnabled();
	void SetLightEnabled(bool b);
	void SetBillboard(bool b);
	bool IsBillboard();
	void SetColor(Vector3 color);
	Material GetMaterial();
	void Update(double dt) override;
};
