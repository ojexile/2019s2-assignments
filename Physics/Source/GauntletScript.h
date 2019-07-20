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
public:
	GauntletScript();
	virtual ~GauntletScript();
	virtual void Start() override;
	void RotateFoward();
	void RotateBackward();

	void Use();
};
