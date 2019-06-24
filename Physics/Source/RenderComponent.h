#pragma once
#include "ComponentBase.h"
#include "Mesh.h"

class RenderComponent :
	public ComponentBase
{
private:
	Mesh* m_Mesh;
	bool m_bLightEnabled;
public:
	RenderComponent(Mesh* mesh);
	virtual ~RenderComponent();

	Mesh* GetMesh();
	bool GetLightEnabled();

	void Update(double dt) override;
};

