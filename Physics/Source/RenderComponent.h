#pragma once
#include "ComponentBase.h"
#include "Mesh.h"

class RenderComponent :
	public ComponentBase
{
private:
	Mesh* m_Mesh;
	bool m_bLightEnabled;
	bool m_bBillboard;
public:
	RenderComponent(Mesh* mesh);
	virtual ~RenderComponent();
	virtual ComponentBase* Clone()
	{
		return new RenderComponent(*this);
	}

	Mesh* GetMesh();
	bool GetLightEnabled();
	void SetLightEnabled(bool b);
	void SetBillboard(bool b);
	bool IsBillboard();

	void Update(double dt) override;
};
