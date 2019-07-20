#pragma once
#include "ScriptComponent.h"
#include "MeshController.h"
class GauntletScript :
	public ScriptComponent
{
public:
	enum eSTONES
	{
		NONE,
		SOUL,
		REALITY,
		SPACE,
		POWER,
		TIME,
		MIND,

		TOTAL,
	};
private:
	eSTONES m_eStone;
	MeshController<Mesh>* m_MC;
	bool m_bInUse;
public:
	GauntletScript();
	virtual ~GauntletScript();
	virtual ComponentBase* Clone()
	{
		return new GauntletScript(*this);
	}
	virtual void Start() override;
	void RotateForward();
	void RotateBackward();

	void Use();
};
